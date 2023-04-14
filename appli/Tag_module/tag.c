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
#define nbState 2
#define nbEvent 6

// PRIVATE TYPES ---------------------------------------------------------------

typedef enum {
	S_DEATH,
	Empty,
	Loaded
}State;

typedef enum{
	'?',
	'L',
	'S',
	'.'
}Event

typedef enum {
	loadMem,
	setSerial,
	printSerial,
	sleep,
	storeMem,
	stop
}action;

typedef


// PRIVATE FUNCTIONS DECLARATIONS ----------------------------------------------



// PRIVATE CONSTANTS -----------------------------------------------------------
struct tag_t{
	uint32_t flash_address;
	uint32_t ram_buffer;
	State state;
	uint32_t serialNumber;};



// PRIVATE FUNCTIONS DEFINITIONS -----------------------------------------------



// PUBLIC FUNCTIONS DEFINITIONS ------------------------------------------------

extern Tag* Tag_new(uint32_t mem_address)
{
	Tag* this;
	this=(Tag* )malloc(sizeof(Tag));


	this->state = S_DEATH;
	this->flash_address = mem_address;
	this->ram_buffer = EMPTY_SERIAL;
	this->serialNumber = 0;
	return this;
}

extern void Tag_start(Tag *this){
	printf("Saisissez votre commande :");
}

extern void Tag_setSerial(Tag *this, uint32_t serial){
	this->serialNumber = serial;
}

extern void Tag_printSerial(Tag* this){
	printf("Serial Number: %d", this->serialNumber);
}

extern void Tag_sleep(Tag *this){

}

extern void Tag_storeMem(Tag* this){
	FLASH_set_word(this->flash_address, this->serialNumber);
}

extern void Tag_loadMem(Tag* this){
	this->serialNumber = FLASH_read_word(this->flash_address);
}

extern void Tag_stop(Tag *this){
	this->state = S_DEATH;
	Tag_free(this);
}

extern void Tag_free(Tag *this){
	free(this);
}

void Tag_run(Tag *this){
	switch(State){
	case Empty: //Tag not loaded -> No Serial number in RAM
		switch(Action){
			case loadMem:
				Tag_loadMem(this);
				this->state = Loaded;
				break;
			case setSerial:
				Tag_setSerial(this,23); // TODO add var for serial 
				this->state = Loaded;
				break;
			default: 
				printf("Tag non initialisé");
				break;
		}
		break;
	case Loaded: // Tag loaded -> Serial Number this->serialNumber
		break;
	}
}