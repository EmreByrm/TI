#include "inc/tm4c123gh6pm.h"
#include "stdint.h"



void main(void)
{
//    1. Enable the ADC clock using the RCGCADC register

    SYSCTL_RCGCADC_R |= (1<<0);

//    2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
//    To find out which GPIO ports to enable, refer to “Signal Description” on page 801.

    SYSCTL_RCGCGPIO_R |= (1<<4);

//    3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
//    configure, see Table 23-4 on page 1344.

    GPIO_PORTE_AFSEL_R |= (1<<3);

//    4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
//    GPIO Digital Enable (GPIODEN) register (see page 682).

    GPIO_PORTE_DEN_R &= (0<<3);

//   5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
//   the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.

    GPIO_PORTE_AMSEL_R |= (1<<3);

//    6. If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI
//    register. The default configuration has Sample Sequencer 0 with the highest priority and Sample
//    Sequencer 3 as the lowest priority.

//    Sample Sequencer Configuration
//    Configuration of the sample sequencers is slightly more complex than the module initialization
//    because each sample sequencer is completely programmable.
//    The configuration for each sample sequencer should be as follows:


//    1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
//    ADCACTSS register. Programming of the sample sequencers is allowed without having them
//    enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
//    event were to occur during the configuration process.

    ADC0_ACTSS_R &= (0<<3);

//    2. Configure the trigger event for the sample sequencer in the ADCEMUX register.

    ADC0_EMUX_R &= 0x0FF;

//    3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
//    (ADCTSSEL) register to specify in which PWM module the generator is located. The default
//    register reset selects PWM module 0 for all generators.

//    4. For each sample in the sample sequence, configure the corresponding input source in the
//    ADCSSMUXn register.

    ADC0_SSMUX3_R = 0;

//   5. For each sample in the sample sequence, configure the sample control bits in the corresponding
//    nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
//    is set. Failure to set the END bit causes unpredictable behavior.

    ADC0_SSCTL3_R |= (1<<1) | (1<<2);

//    6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.

//    7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
//    register.
    ADC0_ACTSS_R |= (1<<3);

    /* PORTF AYARLARI */

    SYSCTL_RCGCGPIO_R |= 0x20;   // PortF enerjilendirildi -> PORT Enerjilendirmek için kullanýlan kod normalde SysCtlPeriperhalEnable(SYSCTL_PERIPH_GPIOF);

    /* GPIO Pinlerinde PC 0-3, PD7 ve PF0 pinleri kilitli olarak gelir. Bunlarda push pull ve pull up kullanmak için yada bu pinleri
    * kullanmak için açmamýz gerekli. Bunu iki komut ile yapýyoruz. GPIO Commit ve GPIO Lock. Bunlarý komutlardan önce açmamýz gerekiyor.
    */

    GPIO_PORTF_DIR_R |= 0x0E;    // 0E yazarak 1,2 ve 3. pinleri output yaptýk.
    GPIO_PORTF_DEN_R |= 0x1F;    // 0,1,2 3 ve 4.  pinleri dijital enable yaptýk.

    while(1)
    {
        ADC0_PSSI_R |= (1<<3);   /* Enable SS3 conversion or start sampling data from AN0 */
        while((ADC0_RIS_R & 8) == 0) ;   /* Wait untill sample conversion completed*/
                uint32_t adc_value = ADC0_SSFIFO3_R; /* read adc coversion result from SS3 FIFO*/
                ADC0_ISC_R = 8;          /* clear coversion clear flag bit*/
                    /*control Green PF3->LED */
                    if(adc_value >= 2048)
            GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
            else if(adc_value < 2048)
            GPIO_PORTF_DATA_R  = 0x00; /* turn off green LED*/
    }





}



