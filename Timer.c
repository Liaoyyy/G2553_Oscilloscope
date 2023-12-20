/*
 * Timer.c
 *
 *  Created on: 2023Äê12ÔÂ14ÈÕ
 *      Author: liaoyang
 */

#include <Timer.h>

void Timer_initConfig(void)
{
    //Use TimerA to finish timed ADC task
    TA0CTL =0;//Clear
    TA0CTL |= TASSEL_2;//SMCLK
    TA0CTL |= MC_1;//Up to CCR0
    TA0CTL |= ID_0;//divider 1
    TA0CTL |= TAIE;//enable interrupt

    //100000Hz interrupt
    TA0CCR0 = 10 - 1;

    //use Timer1 to measure the PWM frequency
    TA1CTL |= TASSEL_2;//SMCLK 1MHz
    TA1CTL |= MC_1;//Up to CCR0
    TA1CTL |= ID_3;//divider 8
    TA1CTL |= TAIE;
    TA1CCTL1 |= CCIE+CAP+CM_1+SCS+CCIS_0;

    TA0CCR0 = 62500 - 1;
}

