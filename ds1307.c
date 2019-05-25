// ds1307.c
//
// 23-05-2019
//


#include "ds1307.h"


uint8_t rtc[8];  //for ds1307 registers data



//-----------------------------------------------------------------------------
void rtc_conv_data(uint8_t *d, uint8_t m)  //d-data //m-mask
    {
    *d=(((((*d & m)>>4)<<1)+(((*d & m)>>4)<<3))+(*d & 0x0F));
    }


//-----------------------------------------------------------------------------
void rtc_read(uint8_t *data)
    {
    i2c_start();
    i2c_send_byte(DS1307 | WRITE);

    i2c_send_byte(0x00);

    i2c_start();

    i2c_send_byte(DS1307 | READ);

    for(uint8_t i=0; i<7; i++) data[i] = i2c_read_byte(I2C_ACK);

    data[7] = i2c_read_byte(I2C_NACK);

    i2c_stop();

    rtc_conv_data(&data[0], 0x70);
    rtc_conv_data(&data[1], 0x70);
    rtc_conv_data(&data[2], 0x30);
    rtc_conv_data(&data[4], 0x30);
    rtc_conv_data(&data[5], 0x10);
    rtc_conv_data(&data[6], 0xF0);
    }


//-----------------------------------------------------------------------------
void rtc_write_reg(uint8_t addr, uint8_t val)
    {
    i2c_start();
    i2c_send_byte(DS1307 | WRITE);

    i2c_send_byte(addr);
    i2c_send_byte(val);

    i2c_stop();
    }


//-----------------------------------------------------------------------------
uint8_t rtc_read_reg(uint8_t addr)
    {
    i2c_start();
    i2c_send_byte(DS1307 | WRITE);

    i2c_send_byte(addr);

    i2c_start();
    i2c_send_byte(DS1307 | READ);

    uint8_t data = i2c_read_byte(I2C_NACK);

    i2c_stop();

    return data;
    }


//-----------------------------------------------------------------------------
void rtc_init(void)
    {
    uint8_t temp=0;

    temp = rtc_read_reg(0x00);
    rtc_write_reg(0x00, temp & 0b01111111); //rtc start

    temp = rtc_read_reg(0x02);
    rtc_write_reg(0x02, temp & 0b10111111); //set 24-hour mode

    rtc_write_reg(0x07, 0b10000000);
    }


//-----------------------------------------------------------------------------
void rtc_set_sec(uint8_t val)
    {
    rtc_write_reg(0x00, (((val/10)<<4)+(val%10)) & 0b01111111);
    }


//-----------------------------------------------------------------------------
void rtc_set_min(uint8_t val)
    {
    rtc_write_reg(0x01, (((val/10)<<4)+(val%10)) & 0b01111111);
    }


//-----------------------------------------------------------------------------
void rtc_set_hrs(uint8_t val)
    {
    rtc_write_reg(0x02, (((val/10)<<4)+(val%10)) & 0b10111111);
    }


//-----------------------------------------------------------------------------
void rtc_set_day(uint8_t val)
    {
    rtc_write_reg(0x03, (val & 0b00000111));
    }


//-----------------------------------------------------------------------------
void rtc_set_dat(uint8_t val)
    {
    rtc_write_reg(0x04, (((val/10)<<4)+(val%10)) & 0b00111111);
    }


//-----------------------------------------------------------------------------
void rtc_set_mon(uint8_t val)
    {
    rtc_write_reg(0x05, (((val/10)<<4)+(val%10)) & 0b00011111);
    }


//-----------------------------------------------------------------------------
void rtc_set_year(uint8_t val)
    {
    rtc_write_reg(0x06, ((val/10)<<4)+(val%10));
    }


