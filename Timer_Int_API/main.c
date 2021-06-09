#include "stdint.h"
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include  "inc/hw_memmap.h"
#include "driverlib/sysctl.c"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.c"
#include "driverlib/timer.h"
#include "driverlib/timer.c"
#include "driverlib/interrupt.h"

void Config_Set();
void timer_Set();
void timerInt()
{

        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1))
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,2);
        }
}

void main(void)
{
   Config_Set();
   timer_Set();
   while(1)
   {

   }


}

void Config_Set()
{

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

}
void timer_Set()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   // Timer Aktif Edildi.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 40000000);


    /* GLOBAL AYARLAR */

    IntMasterEnable();
    IntEnable(INT_TIMER0A);

    /* YEREL AYARLAR */
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerInt);


    TimerEnable(TIMER0_BASE, TIMER_A);
}
