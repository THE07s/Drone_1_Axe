/**
 *******************************************************************************
 * @file 	main.c
 * @author 	Drone_1_Axe Team
 * @date 	Avril 23, 2025
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */
 
#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include <stdio.h>
#include <math.h>

// Inclusion des modules de l'application
#include "src/sensors.h"
#include "src/display.h"
#include "src/user_input.h"
#include "src/motor_control.h"
#include "src/stabilization.h"

#define BLINK_DELAY		50	//ms
#define BLINK_DELAY2	10  //ms
int constante = 0;
char str[32];

/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	/* Cette ligne doit rester la première de votre main !
	 * Elle permet d'initialiser toutes les couches basses des drivers (HAL),
	 * condition préalable indispensable à l'exécution des lignes suivantes.
	 */
	HAL_Init();

	/* Initialisation des périphériques utilisés dans votre programme */
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);

	/* Indique que les printf sont dirigés vers l'UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	
	/* Initialisation des modules */
	init_user_input();  // Initialise les entrées utilisateur
	init_display();     // Initialise l'écran ILI9341
	init_sensors();     // Initialise le capteur MPU6050
	init_motors();      // Initialise les moteurs
	init_stabilization(); // Initialise le système de stabilisation

	/* Hello student */
	printf("Drone 1 Axe - Système démarré\r\n");

	/* Tâche de fond, boucle infinie */
	while (1)
	{		
		if (constante < 240) // Évite de dépasser les limites de l'écran (240x320)
		{
			

			// Affichage des données
			display_angle(resultat_deg);
			display_inclination_line(0, y1, 320, constante, ILI9341_COLOR_RED);
						
			HAL_Delay(BLINK_DELAY);
		}
		
		// Gestion du clignotement LED si input reçu
		if (char_received(UART2_ID))
		{
			write_LED(true);
			HAL_Delay(BLINK_DELAY);
			write_LED(false);
			constante += 1;
		}
	}
}
