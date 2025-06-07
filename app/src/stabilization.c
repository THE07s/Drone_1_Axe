/**
 *******************************************************************************
 * @file    stabilization.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'algorithme de stabilisation
 *******************************************************************************
 */

#include "stabilization.h"
#include "motor_control.h" // Pour ESC_PULSE_MIN/MAX
#define ESC_PULSE_MIN   275U    // 1100 µs / 4000 µs = 27,5 % → valeur 275/1000
#define ESC_PULSE_MAX   485U    // 1940 µs / 4000 µs = 48,5 % → valeur 485/1000
#include "state.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "stm32g4xx_hal.h"

void process_stabilization(float angle_system, float angle_commande) {
    // Correction proportionnelle
    const float Kp = 3.0f;
    float erreur = angle_commande - angle_system;
    float correction = Kp * erreur;

    // Impulsions de base (moteurs à l'arrêt ou au minimum)
    const uint16_t pulse_base = (ESC_PULSE_MAX - ESC_PULSE_MIN) / 2 + ESC_PULSE_MIN; // Centre autour de la valeur médiane
    const uint16_t pulse_max = ESC_PULSE_MAX;

    // Correction proportionnelle (on centre autour de pulse_base)
    int16_t pulse_moteur1 = (int16_t)(pulse_base + correction);
    int16_t pulse_moteur2 = (int16_t)(pulse_base - correction);

    // Saturation pour rester dans les bornes
    if (pulse_moteur1 > pulse_max) pulse_moteur1 = pulse_max;
    if (pulse_moteur1 < pulse_base) pulse_moteur1 = pulse_base;
    if (pulse_moteur2 > pulse_max) pulse_moteur2 = pulse_max;
    if (pulse_moteur2 < pulse_base) pulse_moteur2 = pulse_base;

    // Application aux moteurs
    set_moteur(1, (uint16_t)pulse_moteur1);
    // set_moteur(2, (uint16_t)pulse_moteur2);

    g_state.asservissement_value = (float)correction;
}