/*
 * SPI.h
 *
 *  Created on: 2023Äê12ÔÂ14ÈÕ
 *      Author: liaoyang
 */
#ifndef SPI_H_
#define SPI_H_

#include <msp430.h>
#include <main.h>
#include <Config.h>

/* Function define */
#define SDA_LOW     LCD_SDA_OUTPORT &= ~LCD_SDA_BIT
#define SDA_HIGH    LCD_SDA_OUTPORT |= LCD_SDA_BIT
#define SCLK_HIGH   LCD_SCLK_OUTPORT |= LCD_SCLK_BIT    // clock
#define SCLK_LOW    LCD_SCLK_OUTPORT &= ~LCD_SCLK_BIT
#define DATA        LCD_A0_OUTPORT |= LCD_A0_BIT        // send data
#define COMMAND     LCD_A0_OUTPORT &= ~LCD_A0_BIT       // send command
#define RESET       LCD_RESET_OUTPORT &= ~LCD_RESET_BIT // clear LCD
#define RUN         LCD_RESET_OUTPORT |= LCD_RESET_BIT  // allow to display


void SPI_initConfig(void);

void sendByte(u8 item);
void sendCommand(u8 cmd);
void sendData(u8 * pValues,u8 cnt);
#endif /* SPI_H_ */



