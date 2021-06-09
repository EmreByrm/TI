#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "stdint.h"

#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned int *)0x400FE608)) // Bu Register bize GPIO Clocklarýný enerjilendirmeye yarýyor.
#define GPIO_PORTF_DIR_R        (*((volatile unsigned int *)0x40025400)) // Bu Register bize pinleri input veya output olarak ayarlama imkaný saðlýyor. 1 Output,0 Ýnput
#define GPIO_PORTF_DEN_R        (*((volatile unsigned int *)0x4002551C)) // Dijital Enable Registeri
#define GPIO_PORTF_DATA_R       (*((volatile unsigned int *)0x400253FC)) // DATA registeri

void main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;   // PortF enerjilendirildi -> PORT Enerjilendirmek için kullanýlan kod normalde SysCtlPeriperhalEnable(SYSCTL_PERIPH_GPIOF);
    GPIO_PORTF_DIR_R |= 0x0E;    // 0E yazarak 1,2 ve 3. pinleri output yaptýk.
    GPIO_PORTF_DEN_R |= 0x0E;    // 1,2 ve 3. pinleri dijital enable yaptýk.
    GPIO_PORTF_DATA_R |= 0x0E;   // 2 yazarsak 1. pin aktif olur. 4 yazarsak 2.pin aktif olur. 8 yazarsak 3.pin aktif olur

    /* ***************************** HWREG KOMUTU ************************** */
/*
    HWREG(0x400FE608)|= 0x20;
    HWREG(0x40025400)|= 0x0E;
    HWREG(0x4002551C)|= 0x0E;
    HWREG(0x400253FC)|= 0x0E;
    */
}

