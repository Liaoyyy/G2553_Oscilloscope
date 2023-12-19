#include <msp430.h> 
#include <main.h>
#include <Config.h>
#include <GPIO.h>
#include <SPI.h>
#include <LCD.h>
#include <ADC.h>
#include <Timer.h>

void Clk_initConfig(void);

unsigned short ADC_Buf[16];//contain ADC data


float TimerFreq=1000000;//1MHz
long int pulseStart=0;  //positive edge start time
long int pulseStop=0;   //next positive edge start time
int overflowCnt=0; //overflow times
float period=0; //period length
float freq=0.0; //frequency

const unsigned long demoPal [ 7 ] = {
   // seven meaningful color codes - BLU GREEN CYAN RED MAUVE YELLOW WHITE
   0xFFL, 0xFF00L, 0xFFFFL, 0xFF00000L, 0xFF00FFL, 0xFFFF00L, 0xFFFFFFL };
#define INDEX_MODULUS (sizeof(demoPal) / sizeof(demoPal[0]))


unsigned ColorIndex;  // points into demoPallete[]
unsigned square_num, offset;
/**
 * main.c
 */
int main(void)
{
    int cnt = 1;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clk_initConfig();
	GPIO_initConfig();
//	Timer_initConfig();
//	ADC_initConfig();
    SPI_initConfig();
    LCD_initConfig();

    LCD_clear();
	ADC_START;
	_enable_interrupt();
	Rotate();
	show_string(20,115,"Freq:",0xFF,12);
    for(cnt = 160;cnt >=0; cnt--){
        draw_point(cnt,110,demoPal[1]);
    }
	for(;;)
	{
	}
}



//TODO: 数据采样后直接发送？还是用FIFO装后发送？
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_ISR(void)
{
    int i = 0;
    float sum=0;
    switch(TAIV)
    {
        case 0x0A:
        {
            for(i =0; i<16;i++)
            {
                sum+=(ADC_Buf[i])*(3.3)/1023;
            }
            ADC10SA=(unsigned short)ADC_Buf;
            ADC_START;
            break;
        }
        default:break;
    }
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    ADC10CTL0 &= ~ADC10IFG;//clear ADC interrupt
}

//TODO: optimize the frequency measure part
int flag=0;
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_ISR(void)
{
    switch(TA1IV)
    {
        case 0x02:
        {
            if(flag==0)
            {
                pulseStart = TA1CCR1;
                flag = 1;
            }
            else if(flag)
            {
                pulseStop = TA1CCR1;
                period = pulseStop - pulseStart + 65536*overflowCnt;
                freq = TimerFreq/(float)period;
                overflowCnt=0;
                flag = 0;
            }
            break;
        }
        //overflow
        case 0x0A:
            if(flag==1){
                overflowCnt++;
                break;
            }
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
