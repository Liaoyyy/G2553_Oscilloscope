/*
 * GPIO.h
 *
 *  Created on: 2023Äê12ÔÂ17ÈÕ
 *      Author: liaoyang
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <Config.h>

void GPIO_initConfig(void);

#define LED_TOGGLE P1OUT ^= BIT6;

#endif /* GPIO_H_ */
