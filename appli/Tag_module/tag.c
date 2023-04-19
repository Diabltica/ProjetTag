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
	S_EMPTY,
	S_LOADED,
	S_SLEEP,
	S_DEATH
}State;

typedef enum {
	A_NOP = 0, // Aucune action
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

typedef enum{
	E_SET,
	E_LOAD,
	E_PRINT,
	E_SLEEP,
	E_STORE,
	E_STOP
}Event;

static Transition mySm[NB_STATE][NB_EVENT] =  {{},
											   {{S_LOADED,A_SET_SERIAL},
											   {S_LOADED,A_LOAD_MEM},
											   {},{},{},

											   {S_DEATH,A_STOP}}, // State Empty
											  
											  {{S_LOADED,A_SET_SERIAL},
											   {S_LOADED,A_LOAD_MEM},
											   {S_LOADED,A_PRINT_SERIAL},
											   {S_LOADED,A_SLEEP},
											   {S_SLEEP,A_STORE_MEM},
											   {S_DEATH,A_STOP}}, // State Loaded 
											  
											  {{S_LOADED, A_LOAD_MEM},
 											   {S_LOADED, A_SET_SERIAL},
 											   {S_LOADED, A_PRINT_SERIAL},{},
											   {S_LOADED, A_STORE_MEM},
 											   {S_DEATH, A_STOP}} // State Sleep
};

typedef void (*ActionPtr)();

// PRIVATE FUNCTIONS DECLARATIONS ----------------------------------------------

void Tag_Nop(void);
void printSerial(Tag *this);
void setSerial(Tag *this);
void sleep(Tag *this);
void storeMem(Tag *this);
void loadMem(Tag *this);
void stop(Tag *this);
extern void Tag_run(Tag *this, Event anEvent);

// PRIVATE CONSTANTS -----------------------------------------------------------
struct tag_t{
	uint32_t flash_address;
	uint32_t ram_buffer;
	State state;
	uint32_t serialNumber;};

static const ActionPtr actionsTab[NB_ACTION] = {&Tag_Nop,
												&loadMem,
												&setSerial,
												&printSerial,
												&sleep,
												&storeMem,
												&stop};


// PRIVATE FUNCTIONS DEFINITIONS -----------------------------------------------

void Tag_Nop(void){} // Do Nothing
void printSerial(Tag *this){
	printf("Serial Number: %d", (int)this->serialNumber);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,1);
}

void setSerial(Tag *this){
	printf("New serial number: %d",(int)this->serialNumber);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,1);
}

void sleep(Tag *this){
	/*HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,0);
	sleep_asm();

}

void storeMem(Tag *this){
	printf("Store Serial %d at %d",(int)this->serialNumber,(int)this->flash_address);
	FLASH_set_word(this->flash_address, this->serialNumber);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,1);
}

void loadMem(Tag *this){
	printf("Load Serial Number at %d",(int) this->flash_address);
	this->serialNumber = FLASH_read_word(this->flash_address);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,1);
}

void stop(Tag *this){
	printf("Goodbye !");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,0);
}

// PUBLIC FUNCTIONS DEFINITIONS ------------------------------------------------

extern Tag* Tag_new(uint32_t mem_address)
{
	Tag* this;
	this=(Tag* )malloc(sizeof(Tag));


	this->state = S_EMPTY;
	this->flash_address = mem_address;
	this->serialNumber = 0;
	return this;
}

extern void Tag_start(Tag *this){
	printf("Saisissez votre commande :");
}

extern void Tag_setSerial(Tag *this, uint32_t serial){
	this->serialNumber = serial;
	Tag_run(this, E_SET);
}

extern void Tag_printSerial(Tag* this){
	Tag_run(this, E_PRINT);
}

extern void Tag_sleep(Tag *this){
	Tag_run(this, E_SLEEP);
}

extern void Tag_storeMem(Tag* this){
	Tag_run(this, E_STORE);
}

extern void Tag_loadMem(Tag* this){
	Tag_run(this, E_LOAD);
}

extern void Tag_stop(Tag *this){
	Tag_run(this, E_STOP);
}

extern void Tag_free(Tag *this){
	if(this != NULL){
		free(this);
	}
}

//Machine à état
extern void Tag_run(Tag *this, Event anEvent){
	Action anAction;
	State aState;

	anAction = mySm[this->state][anEvent].action;
	aState = mySm[this->state][anEvent].destinationState;

	if(aState != S_FORGET){
		actionsTab[anAction](this);
		this->state = aState;
	}
}
