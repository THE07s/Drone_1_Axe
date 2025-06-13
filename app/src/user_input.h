/**
 * @file user_input.h
 * @brief Module de gestion des entrées utilisateur (inutilisé)
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef USER_INPUT_H_
#define USER_INPUT_H_

#include <stdbool.h>
#include "stm32g4_uart.h"
#include "stm32g4_gpio.h"

/**
 * @brief Initialise le module d'entrées utilisateur
 * 
 * @pre Les périphériques UART et GPIO doivent être disponibles
 * @post Le module est prêt à recevoir les commandes utilisateur
 */
void init_user_input(void);

/**
 * @brief Vérifie si un caractère a été reçu sur l'UART
 * 
 * @param uart_id Identifiant de l'UART à vérifier
 * @return true si un caractère est disponible, false sinon
 */
bool char_received(uart_id_t uart_id);

/**
 * @brief Traite les commandes reçues via le clavier
 * 
 * @pre L'UART doit être initialisé
 */
void process_keyboard_input(void);

/**
 * @brief Contrôle l'état d'une LED
 * 
 * @param state État désiré de la LED (true=allumée, false=éteinte)
 */
void write_LED(bool state);

#endif /* USER_INPUT_H_ */