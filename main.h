// main.h
//
// atmega328p fuses: 7f df 06
//
// Program:    3974 bytes (12.1% Full)
// Data:         87 bytes (4.2% Full)
//
// avr8-gnu-toolchain-3.6.1.1752-win32
//
// (^^)~  24-05-2019
//



#ifndef MAIN_H_
#define MAIN_H_



#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/sleep.h>
#include <util/delay.h>

#include "ds1307.h"
#include "at24c32.h"
#include "max7219.h"

#include "bitm.h"


// arduino mini internal LED
#define BOARDLED_BIT   5
#define BOARDLED_PORT  PORTB
#define BOARDLED_DDR   DDRB

#define BOARDLED_CLR   (REG_BIT_CLR(BOARDLED_PORT, BOARDLED_BIT))
#define BOARDLED_SET   (REG_BIT_SET(BOARDLED_PORT, BOARDLED_BIT))
#define BOARDLED_OUT   (REG_BIT_SET(BOARDLED_DDR, BOARDLED_BIT))
#define BOARDLED_INP   (REG_BIT_CLR(BOARDLED_DDR, BOARDLED_BIT))

#define BOARDLED_INIT  BOARDLED_CLR; BOARDLED_OUT
#define BOARDLED_ON    BOARDLED_SET
#define BOARDLED_OFF   BOARDLED_CLR


// for timer2
#define TIMER2_STOP           0b00000000
#define TIMER2_PRESCALER1     0b00000001
#define TIMER2_PRESCALER8     0b00000010
#define TIMER2_PRESCALER32    0b00000011
#define TIMER2_PRESCALER64    0b00000100
#define TIMER2_PRESCALER128   0b00000101
#define TIMER2_PRESCALER256   0b00000110
#define TIMER2_PRESCALER1024  0b00000111


// timer2 overflow frequency
#define CALC_TMR2_FREQ       125
#define FACT_TMR2_PRESCALER  64
#define TIMER2_PRELOAD       (256-(F_CPU/FACT_TMR2_PRESCALER)/CALC_TMR2_FREQ)


#define CALC_SHIFT_TIME  70
#define SHIFT_TIME       (CALC_SHIFT_TIME/(1000/CALC_TMR2_FREQ))

#define CALC_MENU_TIME   200
#define MENU_TIME        (CALC_MENU_TIME/(1000/CALC_TMR2_FREQ))


#endif /* MAIN_H_ */




