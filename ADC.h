/*
 * ADC.h
 *
 *  Created on: 2023Äê12ÔÂ14ÈÕ
 *      Author: liaoyang
 */

#ifndef ADC_H_
#define ADC_H_

#include <msp430.h>

//start ADC
#define ADC_START (ADC10CTL0 |= ENC + ADC10SC)


void ADC_initConfig(void);



#endif /* ADC_H_ */
