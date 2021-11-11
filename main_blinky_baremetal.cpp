/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

//#include "mbed.h"
#include "stm32f446xx.h"
//must have stm32 include to include register memory addresses and structures as they are needed to facilitate
//the functionality of the following code

//#define WAIT_TIME_MS 500 
//DigitalOut led1(LED1);

//Refer to STM32 reference manual for all register information

int main()
{   
    unsigned int i, j;
    RCC->CR &= 0x00000000;      //Reset Clock Control Register
    RCC->CR |= (1<<16);         //Enable High Speed External (HSE) Clock Signal
    while(!(RCC->CR)&(1<<17));  //the 17th bit in the RCC_CR indicates if the HSE is ready, so we wait in a while loop until it is true.
    RCC->CFGR &= 0x00000000;    //Reset Clock Configuration Register
    RCC->CFGR |= 0xA0;          //Now, we are setting the AHB1 prescaler. We set it to 1010 0000 to divide the system clock by 8 in HPRE register.
    RCC->AHB1ENR &= 0x00000000; //GPIOA is connected to the AHB1 bus. So we must reset the bus then enable the clock to the GPIOA register.
    RCC->AHB1ENR |= (1<<0);     //Enable GPIOA within the RCC_AHB1ENR1 Register

    //Configure the desired I/O as output or input in the GPIOx_MODER Register

    GPIOA->MODER |= 0xA8000000; //Use this reset value to reset Port A mode register
    GPIOA->MODER |= (1<<10);    //Enable General Purpose Output Mode (01) on pins 11 and 10 to enable pin 5 on Port A (PA5)
    GPIOA->OTYPER |= 0x00;      //Reset GPIO output type for Port A
    GPIOA->OSPEEDR |=(1<<10);   //Set Port A Pin 5 speed to Medium Speed (01) (Bits 11 and 10)
    GPIOA->PUPDR = 0x64000000;  //Reset value for Port A port pull-up/pull-down register
    GPIOA->PUPDR |= 0x00;       //Set Port A PUPDR as No pull-up or pull-down (00)
    GPIOA->ODR &= 0x00000000;   //Reset Port A Output Data Register


    while (1)
    {
        //Enabling the ODR turns on LED and disabling the ODR turns off the LED. Turning the ODR register on and off achieves a blinking effect.
        GPIOA->ODR = (1<<5);    //Enable Output Data Register on Port A Pin 5
        for(i=0; i<1000000; i++){
            j = j + 0.1;        //check to see of compiler will optimize empty loop with nothing occurring here (i.e. loop body might not be needed)
        }
        GPIOA->ODR = (0<<5);    //Disable Output Data Register on Port A Pin 5
        for(i=0; i<1000000; i++){
            j = j + 0.1;
        }

    }
}
