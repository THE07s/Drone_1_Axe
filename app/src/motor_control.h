/**
 * @file motor_control.h
 * @brief Module de contrôle des moteurs via ESC
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

// Constantes ESC
#define PERIODE_PWM_US  4000   /*!< Période PWM en microsecondes 4000 µs → 250 Hz */
#define ESC_PULSE_MIN   275    /*!< Impulsion minimale ESC : 1100 µs / 4000 µs = 27,5 % */
#define ESC_PULSE_MAX   485    /*!< Impulsion maximale ESC : 1940 µs / 4000 µs = 48,5 % */
// #define ESC_PULSE_MAX   ESC_PULSE_MIN + 26    /*!< [DEBUG] Impulsion maximale "safe" ESC : 1940 µs / 4000 µs = 48,5 % */

// Def Timer pour ESC
#define ESC_1   TIM_CHANNEL_2   /*!< Canal Timer pour ESC 1 : PA12/CH2 */
#define ESC_2   TIM_CHANNEL_1   /*!< Canal Timer pour ESC 2 : PB6/CH1 */

/**
 * @brief Initialise les contrôleurs ESC et leurs moteurs
 * 
 * @post Les moteurs sont arrêtés et prêts à être utilisés
 */
void init_motors(void);

/**
 * @brief Configure le timer pour la génération PWM
 * 
 * @pre Le timer doit être disponible et configuré dans le HAL
 */
void configure_timer_pwm(void);

/**
 * @brief Définit l'impulsion PWM pour un moteur
 * 
 * @param moteur Numéro du moteur (1 ou 2)
 * @param pulse Largeur d'impulsion (entre ESC_PULSE_MIN et ESC_PULSE_MAX)
 * 
 * @pre Le timer PWM doit être initialisé
 * @post L'impulsion est saturée dans les limites autorisées
 */
void set_impulsion(uint8_t moteur, uint16_t pulse);

/**
 * @brief Active un moteur avec une impulsion donnée
 * 
 * @param moteur Numéro du moteur (1 ou 2)
 * @param pulse Largeur d'impulsion (entre ESC_PULSE_MIN et ESC_PULSE_MAX)
 * 
 * @post Le statut du moteur est mis à jour dans g_state
 */
void set_moteur(uint8_t moteur, uint16_t pulse);

/**
 * @brief Arrête un moteur
 * 
 * @param moteur Numéro du moteur (1 ou 2)
 * @post Le moteur est arrêté et son statut mis à jour dans g_state
 */
void arreter_moteur(uint8_t moteur);

#endif