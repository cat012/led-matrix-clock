// main.c
//
// 23-May-2019
//



#include "main.h"

extern uint8_t rtc[8];   //ds1307 data

char strbuff[16];  //string buffer

volatile uint8_t scrcnt=0;

uint16_t keysadc[5] = { 55, 145, 300, 515, 820 };



//=============================================================================
ISR(TIMER2_OVF_vect)  //Timer2 interrupt
    {
    TCNT2=TIMER2_PRELOAD;

    if(scrcnt) scrcnt--;
    }


//-----------------------------------------------------------------------------
uint16_t get_adc(uint8_t admux)
    {
    uint16_t adc=0;
    ADMUX=admux;                    //channel
    REG_BIT_SET(ADCSRA,ADSC);       //start ADC
    while(REG_BIT_IS_CLR(ADCSRA,ADIF)); //wait the end of ADC
    REG_BIT_SET(ADCSRA,ADIF);       //clear flag
    REG_BIT_SET(ADCSRA,ADSC);       //start ADC
    while(REG_BIT_IS_CLR(ADCSRA,ADIF)); //wait the end of ADC
    adc=ADC;
    REG_BIT_SET(ADCSRA,ADIF);       //clear flag
    return adc;
    }


//-----------------------------------------------------------------------------
uint8_t get_key(void)
    {
    uint8_t key = 0;
    uint16_t adc=0;

    adc = get_adc(0b01000000);

    for(uint8_t i=0; i<5; i++)
        {
        if(adc<keysadc[i])
            {
            key=i+1;
            break;
            }
        }
    return key;
    }


//-----------------------------------------------------------------------------
uint8_t check_keys(void)
    {
    uint8_t k=0;
    static uint8_t oldkey;

    uint8_t newkey = get_key();
    if(newkey != oldkey)
        {
        _delay_ms(50);
        newkey = get_key();
        if(newkey != oldkey)
            {
            oldkey = newkey;
            k=newkey;
            }
        }
    return k;
    }


//-----------------------------------------------------------------------------
int main(void)
    {
    L2_INIT;

    sei();

    TCCR2A=0x00;
    TCNT2=TIMER2_PRELOAD;
    TCCR2B=TIMER2_PRESCALER64;
    TIFR2=(1<<TOV2);
    TIMSK2=(1<<TOIE2);  //timer2 interrupt enable

    ACSR=0b10000000;    //comparator disable
    ADCSRB=0b00000000;
    ADCSRA=0b00000111;  //ADC disable //prescaler 128
    ADMUX=0b11000000;   //internal Vref //channel 0

    ACSR=0b10000000;   //comparator disable
    ADCSRB=0x00;
    ADCSRA=0b10000111; //ADC enable //prescaler 128
    DIDR0=0b00000001;  //disable digital input
    ADMUX=0b01000000;  //Vref=Vcc //channel 0

    max7219_init();
    max7219_brightness(3);

    i2c_init();
    rtc_init();

    uint8_t dupd=0; //flag
    uint8_t srst=0; //flag
    uint8_t scrmode=0;

    while(1)
        {
        if(dupd==0)
            {
            dupd=1;
            rtc_read(rtc);

            sprintf(strbuff, "%02u:%02u", rtc[HOURS_REG], (scrmode==3)?rtc[SECONDS_REG]:rtc[MINUTES_REG]);
            max7219_buff_print(8,strbuff);
            }

        if(scrmode>0 && scrcnt==0)
            {
            scrcnt=MENU_TIME;
            if(scrmode==1) max7219_update(8);
            if(scrmode==2) max7219_update(20);
            if(scrmode==3) max7219_update(20);
            dupd=0;
            }

        if(scrmode==0 && scrcnt==0)
            {
            scrcnt=SHIFT_TIME;
            if(max7219_shift(&srst)==0) dupd=0;
            }

        uint8_t key=check_keys();

        switch(key)
            {
            default: break;
            case 0: break;
            case 1: dupd=0; scrcnt=0; if(++scrmode>3) { scrmode=0; srst=1; } break;
            case 2: break;
            case 3: break;
            case 4: dupd=0;
                    scrcnt=0;
                    if(scrmode==1) { int8_t tmp = rtc[2]; if(--tmp<0) tmp=59; rtc_set_hrs(tmp); }
                    if(scrmode==2) { int8_t tmp = rtc[1]; if(--tmp<0) tmp=59; rtc_set_min(tmp); }
                    if(scrmode==3) { rtc_set_sec(0); }
                    break;
            case 5: dupd=0;
                    scrcnt=0;
                    if(scrmode==1) { uint8_t tmp = rtc[2]; if(++tmp>59) tmp=0; rtc_set_hrs(tmp); }
                    if(scrmode==2) { uint8_t tmp = rtc[1]; if(++tmp>59) tmp=0; rtc_set_min(tmp); }
                    if(scrmode==3) { rtc_set_sec(0); }
                    break;
            }
        }
    }


