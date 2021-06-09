/***********************Headers***********************/
#include <stdint.h>
#include  "inc/tm4c123gh6pm.h"/***********************Variables***********************/

uint8_t status;
char data;
/***********************Function Declarations***********************/

void PWMInit(void);

int main(void){

    PWMInit();

    while (1){

    }
}


void PWMInit(void){

    /***********************Clock config***********************/
    SYSCTL_RCGCPWM_R |= 1 << 1; // Enable PWM1 clock.
//    SYSCTL_RCGC0_R |= 0x00100000;// Enable PWM clock.
    while(! SYSCTL_PRPWM_R & SYSCTL_PRPWM_R1);  // Wait till PWM1 ready.
    SYSCTL_RCGCGPIO_R |= 1 << 5;  // Enable GPIOF clock.
    while(! SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5);  // Wait till GPIOF ready.
    SYSCTL_RCC_R |= 1 << 20;   // Enable pwm division.
    SYSCTL_RCC_R &= ~(7 << 17); // Set pwm clock divided by 2.
    /***********************GPIO config***********************/
    GPIO_PORTF_AFSEL_R |= 1 << 1;    // Set PF1 as alternate function.
    GPIO_PORTF_PCTL_R |= 5 << 4; // Set PF1 pin as M1PWM5 pin.
    /***********************PWM config***********************/
    PWM1_2_CTL_R = 0;     // reset value
    PWM1_2_GENA_R |= 0x8C;
    PWM1_2_GENB_R |= 0x80C;
    PWM1_2_LOAD_R |= 320 - 1;  // Pwm frequency 25khz
    PWM1_2_CMPA_R | 320 / 2 - 1; // Duty cycle %50;
    PWM1_2_CMPB_R | 320 / 2 - 1; // Duty cycle %50;

    PWM1_2_CTL_R |= 1 << 0;    // Enable pwm block.
    PWM1_ENABLE_R |= 1 << 5;   // Enable M1PWM5 output.

}
