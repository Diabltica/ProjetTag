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
struct tag_t{
	uint32_t flash_address;
	uint32_t ram_buffer;
	State state;};



// PRIVATE FUNCTIONS DEFINITIONS -----------------------------------------------



// PUBLIC FUNCTIONS DEFINITIONS ------------------------------------------------

extern Tag* Tag_new(uint32_t mem_address)
{
	Tag* this;
	this=(Tag* )malloc(sizeof(Tag));


	this->state = S_DEATH;
	this->flash_address = mem_address;
	this->ram_buffer = EMPTY_SERIAL;

	return this;
}

extern void Tag_start(Tag *this){

}

extern void Tag_setSerial(Tag *this, uint32_t serial){

}
extern void Tag_printSerial(Tag* this){

}
extern void Tag_sleep(Tag *this){

}
extern void Tag_storeMem(Tag* this){

}
extern void Tag_loadMem(Tag* this){
	this->ram_buffer = LOADED_SERIAL;
}

extern void Tag_stop(Tag *this){

}

extern void Tag_free(Tag *this){
	free(this);
}
