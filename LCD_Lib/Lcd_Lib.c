/*
 * Lcd_Lib.c
 *
 *  Created on: 7 Kas 2020
 *      Author: Emre
 */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "Lcd_Lib.h"

void thirtyHex(void);

void LcdSettings(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  GPIOPinTypeGPIOOutput(LCD_PORT_BASE, 0xFF);

  GPIOPinWrite(LCD_PORT_BASE, RS, 0);
  int i = 0;
  for(i = 0;i<3;i++)
  {
      thirtyHex();
  }
  GPIOPinWrite(LCD_PORT_BASE, D4 | D5 | D6 | D7,  0x20 );
  GPIOPinWrite(LCD_PORT_BASE, E, E);
  SysCtlDelay(200);
  GPIOPinWrite(LCD_PORT_BASE, E, 0);
  SysCtlDelay(50000);

  LcdCommand(0x06);
  LcdCommand(0x0F);
  LcdCommand(0x01);
}

void thirtyHex()
{

    SysCtlDelay(50000);
    GPIOPinWrite(LCD_PORT_BASE, D4|D5|D6|D7 , 0x30);
    GPIOPinWrite(LCD_PORT_BASE, E , E);
    SysCtlDelay(200);
    GPIOPinWrite(LCD_PORT_BASE, E, 0);

}

void LcdCommand(unsigned char komut)
{
   GPIOPinWrite(LCD_PORT_BASE, RS, 0);
   GPIOPinWrite(LCD_PORT_BASE, D4 | D5 | D6 | D7, (komut & 0xF0));
   GPIOPinWrite(LCD_PORT_BASE, E, E);
   SysCtlDelay(200);
   GPIOPinWrite(LCD_PORT_BASE, E ,0);

   SysCtlDelay(50000);

   GPIOPinWrite(LCD_PORT_BASE, RS, 0);
   GPIOPinWrite(LCD_PORT_BASE, D4 | D5 | D6 | D7, (komut & 0x0F) << 4);
   GPIOPinWrite(LCD_PORT_BASE, E, E);
   SysCtlDelay(200);
   GPIOPinWrite(LCD_PORT_BASE, E ,0);


}

void LcdClear(void)
{
    LcdCommand(0x01);
}

void Lcdxy(unsigned char Z, unsigned char V)
{

    LcdCommand(0x80 |  (((Z-1)<<6)+(V-1)));


}


void LcdWrite(unsigned char write)
{
      GPIOPinWrite(LCD_PORT_BASE, RS, RS);
      GPIOPinWrite(LCD_PORT_BASE, D4 | D5 | D6 | D7, (write & 0xF0));
      GPIOPinWrite(LCD_PORT_BASE, E, E);
      SysCtlDelay(2000);
      GPIOPinWrite(LCD_PORT_BASE, E ,0);

      SysCtlDelay(50000);

      GPIOPinWrite(LCD_PORT_BASE, RS, RS);
      GPIOPinWrite(LCD_PORT_BASE, D4 | D5 | D6 | D7, (write & 0x0F) << 4);
      GPIOPinWrite(LCD_PORT_BASE, E, E);
      SysCtlDelay(2000);
      GPIOPinWrite(LCD_PORT_BASE, E ,0);

}
void LcdFunction(unsigned char DL, unsigned char N, unsigned char F)
{
    if(DL == 4)
    {
        if(N == 1)
        {
            if(F == 7)
            {
                LcdCommand(0x20);
            }
            else if(F == 10)
            {
                LcdCommand(0x24);
            }
        }
        else if(N == 2)
        {
            if(F == 7)
            {
                LcdCommand(0x28);
            }
            else if(F == 10)
            {
               LcdCommand(0x2C);
            }
        }
    }
    if(DL == 8)
        {
            if(N == 1)
            {
                if(F == 7)
                {
                    LcdCommand(0x30);
                }
                else if(F == 10)
                {
                    LcdCommand(0x34);
                }
            }
            else if(N == 2)
            {
                if(F == 7)
                {
                    LcdCommand(0x38);
                }
                else if(F == 10)
                {
                   LcdCommand(0x3C);
                }
            }
        }
}

void LcdWordSend(unsigned char *dizi, unsigned int uzunluk)
{

    int i =0;
    for(i = 0;i<uzunluk;i++)
    {

        LcdWrite(dizi[i]);
        SysCtlDelay(50000);
    }
}


