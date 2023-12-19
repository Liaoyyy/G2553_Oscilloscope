/*
 * LCD.h
 *
 *  Created on: 2023Äê12ÔÂ17ÈÕ
 *      Author: liaoyang
 */

#ifndef LCD_H_
#define LCD_H_

#include <Config.h>
#include <SPI.h>

/* Command Index
 * There are just part of commands, if you want to know more,
 * please refer to the UserGuide of ST7735S
 * */
#define NOP         0x00 //No operation
#define SW_RESET    0x01 //Software reset
#define SLEEP_OUT   0x11 //Sleep Out
#define DISPLAY_ON  0x29 //Display On
#define CA_SET      0x2A //Column address set
#define RA_SET      0x2B //Row address set
#define RAM_WRITE   0x2C //Memory write
#define COLOR_MODE  0x3A //Color mode
#define HORIZONTAL  0x36 //Rotate

void LCD_initConfig( void );

void setAddress(u8 x1,u8 x2, u8 y1, u8 y2);
void LCD_clear(void);
void Rotate(void);
void draw_point(u8 x, u8 y, unsigned long Color);
void draw_line(u8 x1,u8 x2, u8 y1, u8 y2,unsigned long Color);
void draw_rectangle(u8 x, u8 y,u8 width, u8 height,unsigned long Color);
void show_char(u8 x, u8 y,u8 letterIndex,u8 Color,u8 sizey);
void show_string(u8 x, u8 y,u8 *p,u8 Color,u8 sizey);

#endif /* LCD_H_ */
