// i2c.h
//
// Software I2C
//
// 23-05-2019
//


#ifndef I2C_H_
#define I2C_H_


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "bitm.h"


#define I2C_DELAY  _delay_us(5)


///////////////////////////////////////////////////////////////////////////////

#define I2C_DDR_REG   DDRD
#define I2C_PORT_REG  PORTD
#define I2C_PIN_REG   PIND

#define I2C_SDA_PIN   3
#define I2C_SCL_PIN   4

///////////////////////////////////////////////////////////////////////////////


#define SDA_INP  REG_BIT_CLR(I2C_DDR_REG, I2C_SDA_PIN)
#define SDA_OUT  REG_BIT_SET(I2C_DDR_REG, I2C_SDA_PIN)
#define SDA_SET  REG_BIT_SET(I2C_PORT_REG, I2C_SDA_PIN)
#define SDA_CLR  REG_BIT_CLR(I2C_PORT_REG, I2C_SDA_PIN)

#define SDA_PULL  SDA_INP; SDA_SET
#define SDA_NULL  SDA_OUT; SDA_CLR

#define SDA_IS_SET  REG_BIT_IS_SET(I2C_PIN_REG, I2C_SDA_PIN)

#define SCL_INP  REG_BIT_CLR(I2C_DDR_REG, I2C_SCL_PIN)
#define SCL_OUT  REG_BIT_SET(I2C_DDR_REG, I2C_SCL_PIN)
#define SCL_SET  REG_BIT_SET(I2C_PORT_REG, I2C_SCL_PIN)
#define SCL_CLR  REG_BIT_CLR(I2C_PORT_REG, I2C_SCL_PIN)

#define SCL_PULL  SCL_INP; SCL_SET
#define SCL_NULL  SCL_OUT; SCL_CLR


#define ACK  0
#define NACK 1



void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_send_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t ask);



#endif  //end of I2C_H_



