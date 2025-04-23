/**
 *******************************************************************************
 * @file    motor_control.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour le contrôle des moteurs/hélices
 *******************************************************************************
 */

#include "motor_control.h"
#include "stm32g4_gpio.h"
#include "stm32g4_timer.h"
#include <stdio.h>

// Variables globales
// À définir selon la configuration matérielle

// Initialisation des moteurs
bool init_motors(void) {
    // Code d'initialisation des moteurs à compléter
    return true;
}

// Contrôle de la vitesse du moteur gauche
void set_left_motor_speed(uint8_t speed) {
    // Code de contrôle du moteur gauche à compléter
}

// Contrôle de la vitesse du moteur droit
void set_right_motor_speed(uint8_t speed) {
    // Code de contrôle du moteur droit à compléter
}

// Arrêt des deux moteurs
void stop_motors(void) {
    // Code d'arrêt des moteurs à compléter
}