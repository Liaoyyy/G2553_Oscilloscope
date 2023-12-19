#include <msp430.h> 
#include <main.h>
#include <Config.h>
#include <GPIO.h>
#include <SPI.h>
#include <LCD.h>
#include <ADC.h>
#include <Timer.h>

void Clk_initConfig(void);

//int adc_data_buf[128];//record the voltage data to be printed

int printFlag=-4;
float freq=0.0; //frequency
int dataNum=0;
int adc_data_buf[128];

/**
 * main.c
 */
int main(void)
{
    //int adc_data_buf[128];
    int cnt = 1;
    int i =0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clk_initConfig();
	GPIO_initConfig();
	Timer_initConfig();
	ADC_initConfig();
    SPI_initConfig();
    LCD_initConfig();
    LCD_clear();
	Rotate();
	show_string(20,115,"Freq:",0xFF,12);
    for(cnt = 160;cnt >=0; cnt--){
        draw_point(cnt,110,WHITE);
    }

    _enable_interrupt();
    ADC_START;
    while(1)
    {
        if(printFlag==1)
        {
            printFlag=-4;
            float temp;
            for(cnt=10;cnt<10+128;cnt++)
            {
                //draw_point(cnt,adc_data_buf)
            }
            //ADC_START;
        }

    }
}

unsigned short ADC_Buf[16];//contain ADC data
int adcFlag=0;
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_ISR(void)
{
    int i = 0;
    int sum=0;
    switch(TAIV)
    {
        case 0x0A:
        {
            if(adcFlag==1)
            {
                adcFlag=0;//receive new data

                for(i =0; i< 16;i++)
                {
                    sum = sum + ADC_Buf[i];
                }
                adcFlag=1;
                ADC10SA=(unsigned short)ADC_Buf;

                adc_data_buf[dataNum]=sum/16;

                dataNum++;

                //if the adc_data_buf is not full, continue to sample
                if(dataNum<128)
                {
                    ADC_START;
                }else
                {
                    dataNum = 0;
                }
                break;
            }
        }
        default:break;
    }
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    ADC10CTL0 &= ~ADC10IFG;//clear ADC interrupt
    adcFlag=1;
}

long int posEdgeNum=0;
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_ISR(void)
{
    switch(TA1IV)
    {
        case 0x02:
        {
            posEdgeNum++;
            break;
        }
        //overflow
        case 0x0A:
            freq=posEdgeNum;
            posEdgeNum=0;
            printFlag ++;
        default:break;
    }

    TA1CCTL1 &= ~CCIFG;
    TA1CTL &= ~TAIFG;//clear interrupts
}


void Clk_initConfig(void)
{
    DCOCTL=CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 = DIVS_0;//SMCLK divider1 f=1Mhz
}

void delay(int cnt)
{
    int i = cnt;
    do
    {
      i--;
    } while ( 0 != i);
}
