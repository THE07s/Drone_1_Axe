/**
 *******************************************************************************
 * @file    user_input.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour la gestion des entrées utilisateur
 *******************************************************************************
 */

#include "user_input.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include <stdio.h>

// Variables globales
// À définir selon les besoins

// Initialisation des entrées utilisateur
void init_user_input(void) {
    // Initialisation du port de la led Verte (carte Nucleo)
    BSP_GPIO_pin_config(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    
    // Autres initialisations si nécessaire
}

// Vérification de la réception de caractères sur l'UART
bool char_received(uart_id_t uart_id) {
    if(BSP_UART_data_ready(uart_id)) {
        /* On "utilise" le caractère pour vider le buffer de réception */
        BSP_UART_get_next_byte(uart_id);
        return true;
    }
    else
        return false;
}

// Traitement des entrées clavier
void process_keyboard_input(void) {
    // Code pour traiter les entrées clavier à compléter
}

// Gestion de la LED utilisateur
void write_LED(bool state) {
    HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, state);
}