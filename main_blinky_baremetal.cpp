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
    RCC->CR &= 0x00000000;
    RCC->CR |= (1<<16);
    while(!(RCC->CR)&(1<<17));
    RCC->CFGR &= 0x00000000;
    RCC->CFGR |= 0xA0;          //Clock frequency is decreased and delay will increase by factor of 8
    RCC->AHB1ENR &= 0x00000000;
    RCC->AHB1ENR |= (1<<0);     //was (1<<0)

    GPIOA->MODER |= 0xA8000000; 
    GPIOA->MODER |= (1<<10);
    GPIOA->OTYPER |= 0x00;
    GPIOA->OSPEEDR |=(1<<10);
    GPIOA->PUPDR = 0x64000000;
    GPIOA->PUPDR |= 0x00;
    GPIOA->ODR &= 0x00000000; //might not need this line of code

    //printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (1)
    {

        GPIOA->ODR = (1<<5);
        for(i=0; i<1000000; i++){
            j = j + 0.1;    //check to see of compiler will optimize empty loop with nothing occurring here (i.e. loop body might not be needed)
        }
        GPIOA->ODR = (0<<5);
        for(i=0; i<1000000; i++){
            j = j + 0.1;
        }


        //GPIOA->ODR ^= (1<<5);
        //led1 = !led1;
        //thread_sleep_for(WAIT_TIME_MS);
    }
}
