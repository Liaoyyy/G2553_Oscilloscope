/*
 * LCD.c
 *
 *  Created on: 2023年12月17日
 *      Author: liaoyang
 */
#include "LCD.h"
#include <Font.h>

void LCD_initConfig( void )
{
  sendCommand(SW_RESET);
  delay(100);
  sendCommand(SLEEP_OUT);
  delay(100);
  sendCommand(DISPLAY_ON);
}

/*
 * set column and row address
 * x1: start column(0-128)
 * x2: end column(0-128)
 * y1: start row(0-160)
 * y2: end row(0-160)
 * */
void setAddress(u8 x1,u8 x2, u8 y1, u8 y2)
{
    //TODO:Error check
    u8 data[4];
    data[0] = 0;
    data[2] = 0;

    //set column
    data[1] = x1;
    data[3] = x2;
    sendCommand(CA_SET);
    sendData(data, 4);

    data[1] = y1;
    data[3] = y2;
    sendCommand(RA_SET);
    sendData(data, 4);
}

/*
 * Rotate 90 degree
 * */
void Rotate(void)
{
    u8 data = 0xA8;
    sendCommand(HORIZONTAL);
    sendData(&data,1);
}

/*
 * clear the LCD
 *
 * */
void LCD_clear(void)
{
    draw_rectangle(0, 0, LCD_width+2, LCD_height+2, 0L);
}


/*
 * draw a single point
 *
 * */
void draw_point(u8 x, u8 y, unsigned long Color)
{
    u8 data[3];
    setAddress(x,x,y,y);

    sendCommand(RAM_WRITE);
    data[0] = (unsigned char)(Color >> 16);
    data[1] = (unsigned char)(Color >> 8);
    data[2] = (unsigned char)Color;
    sendData(data,3);

    //No operation
    sendCommand(NOP);
}

/*
 * draw a rectangle
 * x: start column(0-160)
 * y: start row(0-128)
 * */
void draw_rectangle(u8 x, u8 y,u8 width, u8 height,unsigned long Color)
{
    unsigned num_pixels = width * height;
    u8 data[4];

    // abort if the region size is zero
    if (0==num_pixels) return;

    setAddress(x,x+width-1,y,y+height-1);

    sendCommand(RAM_WRITE);
    data[0] = (unsigned char)(Color >> 16);
    data[1] = (unsigned char)(Color >> 8);
    data[2] = (unsigned char)Color;

    // write 3 bytes to the display RAM for each pixel
    do {
      sendData(data,3);
      num_pixels--;
    } while (0 != num_pixels);

    //No operation
    sendCommand(NOP);
}

/*
 * show a char on the LCD board
 * sizey: choose the font size
 * */
void show_char(u8 x, u8 y,u8 letterIndex,u8 Color,u8 sizey)
{
    u8 temp,t=0;
    u16 i,TypefaceNum;
    u8 x0=x; //record the initial position of the char
    u8 sizex = sizey/2;

    letterIndex = letterIndex - ' ';
    TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
    setAddress(x,y,x+sizex-1,y+sizey-1);  //set address

    for(i=0;i<TypefaceNum;i++)
    {
        if(sizey==12)temp=ascii_1206[letterIndex][i];              //调用6x12字体
        else if(sizey==16)temp=ascii_1608[letterIndex][i];       //调用8x16字体
        else if(sizey==24)temp=ascii_2412[letterIndex][i];       //调用12x24字体
        else if(sizey==32)temp=ascii_3216[letterIndex][i];       //调用16x32字体
        else return;
        for(t=0;t<8;t++)
        {
            if(temp&(0x01<<t)) draw_point(x,y,Color);//画一个点
            x++;
            if((x-x0)==sizex)
            {
                x=x0;
                y++;
                break;
            }
        }
    }
}

/*
 * show a string on the LCD board
 * sizey: choose the font size
 * */
void show_string(u8 x, u8 y,u8 *p,u8 Color,u8 sizey)
{
    while(*p!='\0')
    {
        show_char(x,y,*p,Color,sizey);
        x+=sizey/2;
        p++;
    }
}

