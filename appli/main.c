/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_sys.h"
#include "macro_types.h"
#include "stm32f1_gpio.h"
#include "stm32f1_flash.h"

#include "Tag_module/tag.h"

int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();

	//Initialisation UART2
	UART_init(UART2_ID,115200);

	//Redirection stdin stdout stderr
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	// Création du tag
	uint32_t memory_address = 49;
	Tag *eco_tag = Tag_new(memory_address);

	// Démarrage du tag

	Tag_start(&eco_tag);

	while(1)
	{

		//Si on reçoit une donnée
		if( UART_data_ready(UART2_ID) )
		{
			// TODO:  Remove useless comment
			// switch(UART_get_next_byte(UART2_ID))
			// {
			// case '?':
			// 	Tag_printSerial(eco_tag);
			// 	break;
			// case 'L':
			// 	Tag_loadMem(eco_tag);
			// 	break;
			// case 'S':
			// 	Tag_storeMem(eco_tag);
			// 	break;
			// case '.':
			// 	Tag_sleep(eco_tag);
			// 	break;
			// default:
			// 	break;
			// }
			
			for(Event c = E_PRINT; c <= E_STOP; c++){ // On check la validité de la commande
				uint8_t next_byte = UART_get_next_byte(UART2_ID);
				if(next_byte == (char) c){
					Tag_run(eco_tag, next_byte);
					break;
				}
			}
		}
	}
}
