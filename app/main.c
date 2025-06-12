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

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    /* Initialisation des modules */
    // init_user_input();
    init_display();
    init_sensors();
    init_motors();

    /* Message de démarrage */
    printf("Drone 1 Axe - Système démarré\r\n");

    /* Boucle principale */
    while (1) {
        /* Lecture des capteurs et mise à jour des angles */
        calculate_angles();

        /* Traitement de la stabilisation et application aux moteurs */
        process_stabilization(g_state.angle_MPU1, g_state.command_position);

        /* Traitement de l'affichage */
        Mettre_A_Jour_Affichage();

        /* Traitement des entrées utilisateur */
        // process_user_input();
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    /* Cette ligne ne sera jamais atteinte */
    return 0;
}