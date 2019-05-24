// max7219.h
//
// 8x8 LED matrix + IC MAX7219
//
//-----------------
//   Y
// X 0-7
//   |
//   7
//-----------------
//
// (^^)~  24-05-2019
//


#ifndef MAX7219_H_
#define MAX7219_H_



#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "bitm.h"


#define MAX7219_BUFF_SIZE 5*8


/////////////////////////////////////////////////

#define DT_BIT   7
#define DT_PORT  PORTD
#define DT_DDR   DDRD

#define CS_BIT   6
#define CS_PORT  PORTD
#define CS_DDR   DDRD

#define CK_BIT   5
#define CK_PORT  PORTD
#define CK_DDR   DDRD

/////////////////////////////////////////////////


#define DT_CLR  (REG_BIT_CLR(DT_PORT, DT_BIT))
#define DT_SET  (REG_BIT_SET(DT_PORT, DT_BIT))
#define DT_OUT  (REG_BIT_SET(DT_DDR, DT_BIT))
#define DT_INP  (REG_BIT_CLR(DT_DDR, DT_BIT))

#define CK_CLR  (REG_BIT_CLR(CK_PORT, CK_BIT))
#define CK_SET  (REG_BIT_SET(CK_PORT, CK_BIT))
#define CK_OUT  (REG_BIT_SET(CK_DDR, CK_BIT))
#define CK_INP  (REG_BIT_CLR(CK_DDR, CK_BIT))

#define CS_CLR  (REG_BIT_CLR(CS_PORT, CS_BIT))
#define CS_SET  (REG_BIT_SET(CS_PORT, CS_BIT))
#define CS_OUT  (REG_BIT_SET(CS_DDR, CS_BIT))
#define CS_INP  (REG_BIT_CLR(CS_DDR, CS_BIT))


#define MAX7219_SERIAL_INIT  CS_SET; CS_OUT; CK_CLR; CK_OUT; DT_CLR; DT_OUT



extern const uint8_t font3x7[];


void max7219_init(void);
void max7219_brightness(uint8_t value);
void max7219_shutdown(uint8_t mode);

void max7219_buff_pixel(uint8_t xpos, uint8_t ypos, uint8_t on);

void max7219_buff_char(uint8_t xpos, uint8_t code);
void max7219_buff_print(uint8_t xpos, const char *str);

void max7219_update(uint8_t xpos);
uint8_t max7219_shift(uint8_t *reset);



#endif /* MAX7219_H_ */


