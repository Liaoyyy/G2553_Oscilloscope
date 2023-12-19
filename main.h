/*
 * main.h
 *
 *  Created on: 2023Äê12ÔÂ17ÈÕ
 *      Author: liaoyang
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned   char       uint8_t;
typedef unsigned short     int        uint16_t;
typedef   uint8_t       u8;   //8bit
typedef   uint16_t   u16;     //16bit

#define ADC_len 128

#define BLUE 0xFFL
#define GREEN 0xFF00L
#define RED 0xFF00000L
#define YELLOW 0xFFFF00L
#define WHITE 0xFFFFFFL

void delay(int cnt);
#endif /* MAIN_H_ */
