/*
 * tag.c
 *
 *  Created on: 24 mar. 2023
 *      Author: jjousse
 */


#include "tag.h"
#include "assert.h"
#include "stm32f1_flash.h"
#include "stm32f1xx_ll_pwr.h"
#include "malloc.h"

// PRIVATE DEFINES -------------------------------------------------------------

#define EMPTY_SERIAL	(0xFFFFFFFF)

// PRIVATE TYPES ---------------------------------------------------------------



// PRIVATE FUNCTIONS DECLARATIONS ----------------------------------------------



// PRIVATE CONSTANTS -----------------------------------------------------------



// PRIVATE FUNCTIONS DEFINITIONS -----------------------------------------------



// PUBLIC FUNCTIONS DEFINITIONS ------------------------------------------------

extern Tag* Tag_new(uint32_t mem_address)
{
	Tag* this;
	...

	this->state = S_DEATH;
	this->flash_address = mem_address;
	this->ram_buffer = EMPTY_SERIAL;

	...
}


