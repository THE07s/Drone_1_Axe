/**
 * @file stabilization.c
 * @brief Implémentation du module d'asservissement et de stabilisation via un correcteur proportionnel
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#include "stabilization.h"
#include "../config.h"

void process_stabilization(float angle_system, float angle_commande) {
    const float Kp = 0.8;  // Gain
    float erreur = angle_commande - angle_system;
    
    // Calcul commande correction
    float correction = Kp * erreur;

    // Conversion correction en PWM
    float correction_pwm = correction * (ESC_PULSE_MAX - ESC_PULSE_MIN) / 180.0;

    // MàJ de la correction
    g_state.asservissement_value = correction_pwm;


    // Pulse pour maintient position
    const uint16_t pulse_base = (ESC_PULSE_MAX - ESC_PULSE_MIN) / 2 + ESC_PULSE_MIN; 

    // Calcul impulsions
    int16_t pulse_moteur1 = (int16_t)(pulse_base + correction_pwm);
    int16_t pulse_moteur2 = (int16_t)(pulse_base - correction_pwm);

    // Saturation impulsions limites ESC
    if (pulse_moteur1 > ESC_PULSE_MAX) pulse_moteur1 = ESC_PULSE_MAX;
    if (pulse_moteur2 > ESC_PULSE_MAX) pulse_moteur2 = ESC_PULSE_MAX;
    if (pulse_moteur1 < ESC_PULSE_MIN) pulse_moteur1 = ESC_PULSE_MIN;
    if (pulse_moteur2 < ESC_PULSE_MIN) pulse_moteur2 = ESC_PULSE_MIN;

    // Application aux moteurs selon la configuration
#if USE_MOTOR1
    set_moteur(1, (uint16_t)pulse_moteur1);
#endif

#if USE_MOTOR2
    set_moteur(2, (uint16_t)pulse_moteur2);
#endif

#if DEBUG_MODE
    static uint32_t debug_counter = 0;
    if (++debug_counter >= 1000) { // Affichage tous les 1000 cycles
        printf("Stabilisation - Erreur: %.2f°, Correction: %.2f, M1: %d, M2: %d\r\n", 
               erreur, correction_pwm, pulse_moteur1, pulse_moteur2);
        debug_counter = 0;
    }
#endif
}