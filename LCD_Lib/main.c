#include "Lcd_lib.h"
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{

    LcdSettings();
    SysCtlDelay(50000);
    LcdClear();
    SysCtlDelay(50000);
    LcdFunction(4, 2, 7);
    SysCtlDelay(50000);
    Lcdxy(1,1);
    SysCtlDelay(50000);

    char data[50] ;

    while(1)
    {
        LcdClear();
        SysCtlDelay(50000);
        Lcdxy(1,1);
        LcdWordSend((unsigned char*) data, sprintf(data, "a"));
        SysCtlDelay(50000);
        Lcdxy(2,1 );
        LcdWordSend((unsigned char*) data, sprintf(data, "b"));
        SysCtlDelay(10000000);

    }
}
