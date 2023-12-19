/*
 * GPIO.c
 *
 *  Created on: 2023Äê12ÔÂ17ÈÕ
 *      Author: liaoyang
 */
#include <GPIO.h>
void GPIO_initConfig(void)
{
    //LCD peripheral configuration
    LCD_RESET_DIRPORT |= LCD_RESET_BIT;
    LCD_A0_DIRPORT    |= LCD_A0_BIT;
    LCD_SCLK_DIRPORT  |= LCD_SCLK_BIT;
    LCD_SDA_DIRPORT   |= LCD_SDA_BIT;

    //Timer1 peripheral configuration
    P2SEL |= BIT1;
    P2DIR &= ~BIT1;
}


