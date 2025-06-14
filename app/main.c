/**
 * @file main.c
 * @brief Programme principal du drone 1 axe
 * 
 * Ce fichier contient le point d'entrée et la boucle principale du programme du drone 1 axe. Il initialise tous les modules (affichage, capteurs, moteurs) et exécute la boucle de contrôle principal incluant la lecture des capteurs, la stabilisation et la mise à jour de l'affichage.
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include <stdio.h>

/* Includes spécifiques à l'application --------------------------------------*/
#include "src/display.h"
#include "src/sensors.h"
#include "src/motor_control.h"
#include "src/stabilization.h"

/**
  * @brief  Point d'entrée de votre application
  * @retval int - Code de retour (jamais atteint dans une boucle infinie)
  */
int main(void) {
    /* Initialisation du HAL (doit rester en premier) */
    HAL_Init();

    /* Initialisation des périphériques */
    BSP_GPIO_enable();
    BSP_UART_init(UART2_ID, 115200);
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

#if DEBUG_MODE
    // Effacement de l'écran de debug
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("=== DRONE 1 AXE - MODE DEBUG ===\r\n");
    printf("Configuration:\r\n");
    printf("- Moteur 1: %s\r\n", USE_MOTOR1 ? "ACTIF" : "INACTIF");
    printf("- Moteur 2: %s\r\n", USE_MOTOR2 ? "ACTIF" : "INACTIF");
    printf("- Calibration ESC: %s\r\n", ENABLE_CALIBRATION ? "ACTIVE" : "INACTIVE");
    printf("- Debug capteurs: %s\r\n", DEBUG_SENSORS ? "ACTIF" : "INACTIF");
    printf("===============================\r\n");
#endif

    /* Initialisation des modules */
    // init_user_input();
    init_display();
    init_sensors();
    init_motors();

    /* Message de démarrage */
#if DEBUG_MODE
    printf("Drone 1 Axe - Système démarré (Mode Debug)\r\n");
#else
    printf("Drone 1 Axe - Système démarré\r\n");
#endif

    /* Boucle principale */
    while (1) {
        /* Lecture des capteurs et mise à jour des angles */
        calculate_angles();

        /* Traitement de la stabilisation et application aux moteurs */
        process_stabilization(g_state.angle_MPU1, g_state.command_position);

        /* Traitement de l'affichage */
        update_affichage();

        /* Traitement des entrées utilisateur */
        // process_user_input();
    }
    
#if DEBUG_MODE
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#endif

    /* Cette ligne ne sera jamais atteinte */
    return 0;
}