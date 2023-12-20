/*
 * Timer.c
 *
 *  Created on: 2023年12月14日
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

    //Timer1
    TA1CTL |= TASSEL_2;//SMCLK 1MHz
    TA1CTL |= MC_2;//连续计数模式
    TA1CTL |= ID_0;//1分频
    TA1CTL |= TAIE;
    TA1CCTL1 |= CCIE+CAP+CM_1+SCS+CCIS_0;
}

