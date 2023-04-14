/*
 * blinky_main.c
 *
 *  Created on: 17 janv. 2023
 *      Author: jjousse
 */


#define STM32F103xB
#define DELAY 800000

#include "stm32f1xx.h"
#include <stdint.h>
/*
int main (void){

	//enable clock on GPIO port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


	// now set port A pin 5 to output with max speed of 2MHz and type = push-pull
	GPIOA->CRL &= ~GPIO_CRL_CNF5_Msk;
	GPIOA->CRL |= GPIO_CRL_MODE5_1;
	GPIOA->CRL &= ~GPIO_CRL_MODE5_0;

	//blinking forever
	while (1)
	{

		    GPIOA->ODR |= GPIO_ODR_ODR5_Msk;	//set bit 5: LED green on

		    for (uint32_t i=0; i<=DELAY; i++); // Time ON: delay loop

		    GPIOA->ODR &= ~GPIO_ODR_ODR5_Msk;  //clear bit 5: LED green off

		    for (uint32_t i=0; i<=DELAY; i++); // Time OFF: delay loop
	}
}*/
