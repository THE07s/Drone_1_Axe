/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */
void int_to_str(char, int);
#include "config.h"
#include "stm32g4_sys.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include <stdio.h>

char a = 42;
int b = 42;


#define BLINK_DELAY		100	//ms
#define BLINK_DELAY2	2000 //ms
int constante=0;
char str[32];
sprintf(str, %d, constante);



void int_to_str(str,constante){
	for (i=0, i<strlen(str),i++){


}
}
void write_LED(bool b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool char_received(uart_id_t uart_id)
{
	if( BSP_UART_data_ready(uart_id) )	/* Si un caractère est reçu sur l'UART 2*/
	{
		/* On "utilise" le caractère pour vider le buffer de réception */
		BSP_UART_get_next_byte(uart_id);
		return true;
	}
	else
		return false;
}

void heartbeat(void)
{
	while(! char_received(UART2_ID) )
	{
		write_LED(true);
		HAL_Delay(50);
		write_LED(false);
		HAL_Delay(1500);
	}
}


/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	/* Cette ligne doit rester la première de votre main !
	 * Elle permet d'initialiser toutes les couches basses des drivers (Hardware Abstraction Layer),
	 * condition préalable indispensable à l'exécution des lignes suivantes.
	 */
	HAL_Init();

	/* Initialisation des périphériques utilisés dans votre programme */
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);

	/* Indique que les printf sont dirigés vers l'UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	/* Initialisation du port de la led Verte (carte Nucleo) */
	BSP_GPIO_pin_config(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,GPIO_NO_AF);

	/* Hello student */
	printf("Hi <Student>, can you read me?\n");

	//heartbeat();

	/* Tâche de fond, boucle infinie, Infinite loop,... quelque soit son nom vous n'en sortirez jamais */
	ILI9341_Init();
//	ILI9341_Fill(ILI9341_COLOR_WHITE);
//	ILI9341_DrawCircle(20,20,5,ILI9341_COLOR_BLUE);
//	ILI9341_DrawLine(20,20,100,20,ILI9341_COLOR_RED);
//	ILI9341_DrawLine(20,20,20,100,ILI9341_COLOR_RED);
//	ILI9341_Putc(110,11,'x',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
//	ILI9341_Putc(15,110,'y',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
//	ILI9341_Puts(30,50, "Never gonna give you up, never gonna let you down \n Never gonna run around and desert you \n Never gonna make you cry, never gonna say goodbye \n Never gonna tell a lie and hurt you", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);


	while (1)
	{

		if( char_received(UART2_ID) )
		{
			write_LED(true);		/* write_LED? Faites un ctrl+clic dessus pour voir... */
			HAL_Delay(BLINK_DELAY);	/* ... ça fonctionne aussi avec les macros, les variables. C'est votre nouveau meilleur ami */
			write_LED(false);
		}

		ILI9341_Puts(30,50,  , &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
		HAL_Delay(BLINK_DELAY2);
		constante+=1;

	}
}
