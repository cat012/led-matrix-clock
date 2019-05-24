// max7219.c
//
// 23-05-2019
//


#include "max7219.h"



uint8_t max7219buff[MAX7219_BUFF_SIZE] = {};



//-------------------------------------------------------------------------------------------------
void spi_byte(uint8_t data)  //send byte
    {
    for(uint8_t mask=0x80; mask; mask>>=1)
        {
        (data & mask) ? DT_SET : DT_CLR; //data line
        CK_SET; //clock pulse
        CK_CLR;
        }
    }


//-------------------------------------------------------------------------------------------------
void max7219_write(uint8_t high, uint8_t low)  //send two bytes to IC
    {
    CS_CLR;
    spi_byte(high);
    spi_byte(low);
    CS_SET;
    }


//-------------------------------------------------------------------------------------------------
// pixel on/off  //xpos: 0-  //ypos: 0-7  //on: 0-1
//-------------------------------------------------------------------------------------------------
void max7219_buff_pixel(uint8_t xpos, uint8_t ypos, uint8_t on)
    {
    if(ypos<=7 && xpos<=(MAX7219_BUFF_SIZE-1))
        {
        uint8_t x = xpos;
        uint8_t y = 7-ypos;
        if(on) REG_BIT_SET(max7219buff[x], y);
        else REG_BIT_CLR(max7219buff[x], y);
        }
    }


//-------------------------------------------------------------------------------------------------
// print a character  //xpos: 0-  //character code: 0-255
//-------------------------------------------------------------------------------------------------
void max7219_buff_char(uint8_t xpos, uint8_t code)
    {
    uint8_t c=0;

    if(code>=48 && code<=58) c=code-48;
    else if(code==32) c=11;
    else if(code==43) c=12;
    else if(code==45) c=13;
    else c=14;

    for(uint8_t y=0; y<7; y++)
        {
        for(uint8_t x=0; x<4; x++)
            {
            max7219_buff_pixel((xpos+3)-x, y, REG_BIT_IS_SET(pgm_read_byte(&font3x7[c*8+y]),x));
            }
        }
    }


//-------------------------------------------------------------------------------------------------
// print a string  //x: 0-
//-------------------------------------------------------------------------------------------------
void max7219_buff_print(uint8_t xpos, const char *str)
    {
    for(; *str; xpos+=4) max7219_buff_char(xpos,*str++);
    }


//-------------------------------------------------------------------------------------------------
// send buffer to display  //x: 0-
//-------------------------------------------------------------------------------------------------
void max7219_update(uint8_t xpos)
    {
    for(uint8_t k=0; k<8; k++)
        {
        uint8_t data=0;

        for(uint8_t i=0; i<8; i++)
            {
            if(REG_BIT_IS_SET(max7219buff[i+xpos],(7-k))) REG_BIT_SET(data,(7-i));
            }

         max7219_write(k+1, data);
         }
    }


//-------------------------------------------------------------------------------------------------
uint8_t max7219_shift(uint8_t *reset)
    {
    static uint8_t cnt=0;

    if(*reset) *reset=cnt=0;

    max7219_update(cnt);

    if(++cnt>(MAX7219_BUFF_SIZE-8)) cnt=0;

    return cnt;
    }


//-------------------------------------------------------------------------------------------------
void max7219_shutdown(uint8_t mode)  //mode: 0-shutdown mode, 1-normal operation
    {
    max7219_write(0x0C, mode&0b00000001);
    }


//-------------------------------------------------------------------------------------------------
void max7219_brightness(uint8_t value)  //brightness: 0-15
    {
    max7219_write(0x0A, value&0b00001111);
    }


//-------------------------------------------------------------------------------------------------
void max7219_init(void)
    {
    MAX7219_SERIAL_INIT;  //port init

    max7219_write(0x0C, 0x00);  //Shutdown Register      //shutdown mode
    max7219_write(0x09, 0x00);  //Decode-Mode Register   //no decode
    max7219_write(0x0A, 0x00);  //Intensity Register     //minimum brightness
    max7219_write(0x0B, 0x07);  //Scan-Limit Register    //display all digits
    max7219_write(0x0F, 0x00);  //Display-Test Register  //normal operation

    for(uint8_t k=0; k<8; k++) max7219_write(k+1, 0x00); //clear screen

    max7219_write(0x0C, 0x01);  //Shutdown Register      //normal operation
    }



