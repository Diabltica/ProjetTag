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

int getIntFromUART();

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


	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	// Démarrage du tag

	Tag_start(eco_tag);

	while(1)
	{
		//Si on reçoit une donnée
		if( UART_data_ready(UART2_ID) )
		{
			// TODO:  Remove useless comment
		 switch(UART_get_next_byte(UART2_ID))
			 {
			 case '?':
				 Tag_printSerial(eco_tag);
			 	break;
			 case 's':
				Tag_setSerial(eco_tag,(uint32_t) getIntFromUART());
				break;
			 case 'L':
				Tag_loadMem(eco_tag);
				break;
			 case 'S':
				Tag_storeMem(eco_tag);
			 	break;
			 case '.':
				Tag_sleep(eco_tag);
				break;
			 case 27:
				Tag_stop(eco_tag);
				Tag_free(eco_tag);
				return 0;
				break;
			default:
			 	break;
			}
		}
	}
}

int getIntFromUART() {
    char buffer[16];
    int num = 0;
    printf("\n ENTER SERIAL NUMBER :");

    while (1) {
        char c = UART_getc_blocking(UART2_ID,30000);


        if (c >= '0' && c <= '9') {
            buffer[num++] = c;
        } else if (c == '\n' || c == '\r') {
            break;
        }
    }

    buffer[num] = '\0';


    return atoi(buffer);
}
