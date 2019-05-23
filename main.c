// main.c
//
// 23-May-2019
//



#include "main.h"

extern uint8_t rtc[8];   //ds1307 data

char strbuff[16];  //string buffer

volatile uint8_t shiftscr=0;  //flag



//=============================================================================
ISR(TIMER2_OVF_vect)  //Timer2 interrupt
    {
    TCNT2=TIMER2_PRELOAD;

    static uint8_t cnt0=0;

    if(++cnt0>=7)
        {
        cnt0=0;
        shiftscr=0;
        }
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

    max7219_init();
    max7219_brightness(3);

    i2c_init();
    rtc_init();

//todo  clock set

//delay_ms(2000);

//rtc_set_hrs(13);
//rtc_set_min(54);
//rtc_set_sec(00);

    uint8_t dupd=0; //flag

    while(1)
        {
        if(dupd==0)
            {
            dupd=1;
            rtc_read(rtc);

            sprintf(strbuff, "%02u:%02u", rtc[HOURS_REG], rtc[MINUTES_REG]);
            max7219_buff_print(8,strbuff);
            }

        if(shiftscr==0)
            {
            shiftscr=1;
            if(max7219_shift()==0) dupd=0;
            }
        }
    }


