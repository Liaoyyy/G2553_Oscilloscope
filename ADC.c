/*
 * ADC.c
 *
 *  Created on: 2023Äê12ÔÂ14ÈÕ
 *      Author: liaoyang
 */
#include <ADC.h>
extern unsigned short ADC_Buf[16];

void ADC_initConfig(void)
{
    ADC10CTL0 = ADC10SHT_2+MSC+ADC10ON+ADC10IE; //16 x ADC10CLKs
    ADC10CTL1 = CONSEQ_2+INCH_1;                //A1 input + Repeat single channel
    ADC10AE0 |= BIT1;                           //Analog Enable
    ADC10DTC1 = 16;                             //DTC transfer 16 data each time
    ADC10SA=(unsigned short)ADC_Buf;            //Data Transfer Start Address
}


