/**
 *******************************************************************************
 * @file    user_input.h
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Interface pour la gestion des entrées utilisateur (UART, touches)
 *******************************************************************************
 */

#ifndef USER_INPUT_H_
#define USER_INPUT_H_

#include <stdbool.h>
#include "stm32g4_uart.h"

// Initialisation des entrées utilisateur
void init_user_input(void);

// Vérification de la réception de caractères sur l'UART
bool char_received(uart_id_t uart_id);

// Traitement des entrées clavier
void process_keyboard_input(void);

// Gestion de la LED utilisateur
void write_LED(bool state);

#endif /* USER_INPUT_H_ */