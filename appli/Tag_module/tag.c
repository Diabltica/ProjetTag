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
#define NB_STATE 4
#define NB_EVENT 6
#define NB_ACTION 7

// PRIVATE TYPES ---------------------------------------------------------------

typedef enum {
	S_FORGET = 0, // Pas de changement
	S_DEATH,
	S_EMPTY,
	S_LOADED,
	S_SLEEP
}State;

typedef enum {
	A_NOP, // Aucune action
	A_LOAD_MEM,
	A_SET_SERIAL,
	A_PRINT_SERIAL,
	A_SLEEP,
	A_STORE_MEM,
	A_STOP
}Action;

typedef struct {
	State destinationState;
	Action action;
} Transition;

//Tableau des transitions
static Transition mySm[13][NB_EVENT] = {{S_LOADED, A_LOAD_MEM},
									 	{S_LOADED, A_SET_SERIAL},

										{S_SLEEP, A_SLEEP},
										{S_LOADED, A_LOAD_MEM},
										{S_LOADED, A_SET_SERIAL},
										{S_LOADED, A_STORE_MEM},
										{S_LOADED, A_PRINT_SERIAL},
										{S_DEATH, A_STOP},
											  
										{S_LOADED, A_LOAD_MEM},
										{S_LOADED, A_SET_SERIAL},
										{S_LOADED, A_PRINT_SERIAL},
										{S_LOADED, A_STORE_MEM},
										{S_DEATH, A_STOP}
};

typedef void (*ActionPtr)();

// PRIVATE FUNCTIONS DECLARATIONS ----------------------------------------------

void Tag_Nop(void);

// PRIVATE CONSTANTS -----------------------------------------------------------
struct tag_t{
	uint32_t flash_address;
	uint32_t ram_buffer;
	State state;
	uint32_t serialNumber;};

static const ActionPtr actionsTab[NB_ACTION] = {&Tag_Nop,
												&Tag_loadMem,
												&Tag_setSerial,
												&Tag_printSerial,
												&Tag_sleep,
												&Tag_storeMem,
												&Tag_stop};


// PRIVATE FUNCTIONS DEFINITIONS -----------------------------------------------

void Tag_Nop(void){} // Do Nothing

// PUBLIC FUNCTIONS DEFINITIONS ------------------------------------------------

extern Tag* Tag_new(uint32_t mem_address)
{
	Tag* this;
	this=(Tag* )malloc(sizeof(Tag));


	this->state = S_EMPTY;
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
	printf("Serial Number: %d", (int)this->serialNumber);
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

//Machine à état
extern void Tag_run(Tag *this, Event anEvent){
	Action anAction;
	State aState;

	anAction = mySm[this->state][anEvent].action;
	aState = mySm[this->state][anEvent].destinationState;

	if(aState != S_FORGET){
		actionsTab[anAction]();
		this->state = aState;
	}
}
