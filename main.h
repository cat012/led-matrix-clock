// main.h
//
// atmega328p fuses: 7f df 05
//
// avr8-gnu-toolchain-3.6.1.1752-win32
//
// (^^)~  23-05-2019
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
#define L2_BIT   5
#define L2_PORT  PORTB
#define L2_DDR   DDRB

#define L2_CLR   (REG_BIT_CLR(L2_PORT, L2_BIT))
#define L2_SET   (REG_BIT_SET(L2_PORT, L2_BIT))
#define L2_OUT   (REG_BIT_SET(L2_DDR, L2_BIT))
#define L2_INP   (REG_BIT_CLR(L2_DDR, L2_BIT))

#define L2_INIT  L2_CLR; L2_OUT


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






#endif /* MAIN_H_ */
