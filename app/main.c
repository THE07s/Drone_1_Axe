/**
 *******************************************************************************
 * @file 	main.c
 * @author 	Drone_1_Axe Team
 * @date 	Avril 23, 2025
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include <stdio.h>
#include <math.h>

/* Includes spécifiques à l'application --------------------------------------*/
#include "src/user_input.h"
#include "src/display.h"
#include "src/sensors.h"
#include "src/motor_control.h"
#include "src/stabilization.h"

/* Définitions privées ------------------------------------------------------*/
#define BLINK_DELAY 50  /* Délai de clignotement en ms */

/* Variables globales -------------------------------------------------------*/
static int g_constante;
static char g_str[32];

/* Prototypes de fonctions privées ------------------------------------------*/
static void process_display(void);
static void process_user_input(void);

/**
  * @brief  Point d'entrée de votre application
  * @retval int - Code de retour (jamais atteint dans une boucle infinie)
  */
int main(void)
{
    /* Initialisation du HAL (doit rester en premier) */
    HAL_Init();

    /* Initialisation des périphériques */
    BSP_GPIO_enable();
    BSP_UART_init(UART2_ID, 115200);
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
    
    /* Initialisation des modules applicatifs */
    init_user_input();
    init_display();
    init_sensors();
    init_motors();
    init_stabilization();

    /* Message de démarrage */
    printf("Drone 1 Axe - Système démarré\r\n");

    /* Boucle principale */
    while (1)
    {
        /* Lecture des capteurs */
        read_sensor_data();
        
        /* Traitement de la stabilisation */
        // process_stabilization();
        
        /* Traitement de l'affichage */
        process_display();
        
        /* Traitement des entrées utilisateur */
        process_user_input();
        
        /* Petit délai */
        HAL_Delay(BLINK_DELAY);
    }
    
    /* Cette ligne ne sera jamais atteinte */
    return 0;
}

/**
  * @brief  Traitement de l'affichage
  * @retval None
  */
static void process_display(void)
{
    int y1;
    float angle_rad;
    float angle_deg;
    uint16_t red_color = 0xF800;  /* Couleur rouge en RGB565 */
    
    /* Calculs */
    y1 = 240 - g_constante;
    angle_rad = atan((120.0 - g_constante) / 160.0);
    angle_deg = angle_rad * (180.0 / M_PI);
    
    /* Affichage des informations */
    display_angle(angle_deg, 10, 10);
    display_inclination_line(0, y1, 320, g_constante, red_color);
}

/**
  * @brief  Traitement des entrées utilisateur
  * @retval None
  */
static void process_user_input(void)
{
    if (char_received(UART2_ID))
    {
        write_LED(true);
        HAL_Delay(BLINK_DELAY);
        write_LED(false);
        g_constante++;
    }
}
