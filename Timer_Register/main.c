#include "inc/tm4c123gh6pm.h"
#include "stdint.h"



void main(void)
{
        SYSCTL_RCGCGPIO_R |= 0x20;   // PortF enerjilendirildi -> PORT Enerjilendirmek için kullanýlan kod normalde SysCtlPeriperhalEnable(SYSCTL_PERIPH_GPIOF);

        /* GPIO Pinlerinde PC 0-3, PD7 ve PF0 pinleri kilitli olarak gelir. Bunlarda push pull ve pull up kullanmak için yada bu pinleri
         * kullanmak için açmamýz gerekli. Bunu iki komut ile yapýyoruz. GPIO Commit ve GPIO Lock. Bunlarý komutlardan önce açmamýz gerekiyor.
        */

        GPIO_PORTF_DIR_R |= 0x0E;    // 0E yazarak 1,2 ve 3. pinleri output yaptýk.
        GPIO_PORTF_DEN_R |= 0x1F;    // 0,1,2 3 ve 4.  pinleri dijital enable yaptýk.



//    To use a GPTM, the appropriate TIMERn bit must be set in the RCGCTIMER or RCGCWTIMER
//    register (see page 338 and page 357). If using any CCP pins, the clock to the appropriate GPIO
//    module must be enabled via the RCGCGPIO register (see page 340). To find out which GPIO port
//    to enable, refer to Table 23-4 on page 1344. Configure the PMCn fields in the GPIOPCTL register to
//    assign the CCP signals to the appropriate pins (see page 688 and Table 23-5 on page 1351).
//    This section shows module initialization and configuration examples for each of the supported timer
//    modes.
//
        SYSCTL_RCGCTIMER_R |= (1 <<0);


//    The GPTM is configured for One-Shot and Periodic modes by the following sequence:
//    1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
//    any changes.

      TIMER0_CTL_R = ~(1<<0);

//      2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.

      TIMER0_CFG_R &= 0x00000000;

//      3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
//      a. Write a value of 0x1 for One-Shot mode.
//      b. Write a value of 0x2 for Periodic mode.

      TIMER0_TAMR_R |= 0x02;


//      4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
//      to select whether to capture the value of the free-running timer at time-out, use an external
//      trigger to start counting, configure an additional trigger or interrupt, and count up or down.
//      The timer counts up. When counting up, the timer starts from a
//      value of 0x0.

       TIMER0_TAMR_R |= (1<<4);

//       5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
//       Bizim Clock frekansýmýz 16 MHz. Biz sayýcýmýzý yukarý doðru saymasý için ayarladýk. Bu yüzden
//       yüklememiz gereken baþlangýç deðeri FFFF FFFF(32Bit) - 00F4 2400(16M) = FF0B DBFF

       TIMER0_TAILR_R = 0x00F42400;

//       7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.

       TIMER0_CTL_R = (1<<0);


    while(1)
        {

//        8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
//        the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
//        Register (GPTMICR).

        if((TIMER0_RIS_R & 0x01)==1)    // Sürenin dolup dolmadýðýný kontrol ediyoruz.
        {
            TIMER0_ICR_R |= 0x01; // Timer Interrupt bayraðýný manual temizledik. Interrupt kullanmadýk ama süre dolduðu için temizledik
            GPIO_PORTF_DATA_R ^= 0x02;
        }
        }

}



