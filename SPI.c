/*
 * SPI.c
 *
 *  Created on: 2023Äê12ÔÂ14ÈÕ
 *      Author: liaoyang
 */
#include <SPI.h>

#define SPI_INTERRUPT_ENABLE  IE2 |= UCA0TXIE;  //enable send interrupt
#define SPI_INTERRUPT_DISABLE IE2 &= ~UCA0TXIE;

void SPI_initConfig( void )
{
  //clear LCD
  RESET;
  COMMAND;
  SCLK_LOW;
  SDA_LOW;
  // make sure reset is ACTIVE for a few hundred ms
  delay(100);
  RUN;
  // give the LCD time to complete the RESET actions
  delay(100);
}

/* manually set or reset GPIO to simulate SPI */
void sendByte(u8 item)
{
    unsigned char mask = 0x80;
    do
    {
        if (mask & item)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        SCLK_HIGH;
        SCLK_LOW;
        mask >>= 1;
    }while(mask);
}



void sendCommand(u8 cmd)
{
    COMMAND;
    sendByte( cmd );
}



void sendData(u8 * pValues,u8 cnt)
{

    //error check
    if (0==cnt) return;

    DATA;
    do
    {
      sendByte(*pValues);
      pValues++;
      cnt--;
    } while (cnt);
}


