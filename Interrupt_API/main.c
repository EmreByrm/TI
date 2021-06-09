#include "stdint.h"
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include  "inc/hw_memmap.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.c"

void Config_Set();

void hariciKesme()
{
    int a=GPIOIntStatus(GPIO_PORTF_BASE, true);
        if(a==16)
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,2);
        }
        else if (a==1)
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,4);
        }
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
}

void main(void)
{
   Config_Set();

   while(1)
   {

   }


}
void Config_Set()
{

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); // PF4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // Bu kod ile Pushpull olarak ayarladýk.

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

    /* INTERRUPT */


    /* GLOBAL AYARLAR */

    IntMasterEnable();
    IntEnable(INT_GPIOF);

    /* LOCAL AYARLAR */

    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_INT_PIN_4);
    GPIOIntRegister(GPIO_PORTF_BASE, hariciKesme);


}
