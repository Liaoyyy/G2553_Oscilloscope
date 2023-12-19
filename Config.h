/*
 * Config.h
 *
 *  Created on: 2023Äê12ÔÂ17ÈÕ
 *      Author: liaoyang
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <msp430.h>
//ADC input P1.1

#define LCD_RESET_OUTPORT   P1OUT
#define LCD_RESET_DIRPORT   P1DIR
#define LCD_RESET_BIT       BIT4

#define LCD_A0_OUTPORT  P1OUT
#define LCD_A0_DIRPORT  P1DIR
#define LCD_A0_BIT      BIT3

#define LCD_SCLK_OUTPORT  P1OUT
#define LCD_SCLK_DIRPORT  P1DIR
#define LCD_SCLK_BIT      BIT1

#define LCD_SDA_OUTPORT   P1OUT
#define LCD_SDA_DIRPORT   P1DIR
#define LCD_SDA_BIT       BIT2

#define LCD_width 128
#define LCD_height 160

#endif /* CONFIG_H_ */
