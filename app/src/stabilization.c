#include "stabilization.h"

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

    // Application aux moteurs
    set_moteur(1, (uint16_t)pulse_moteur1);
    // set_moteur(2, (uint16_t)pulse_moteur2);
}