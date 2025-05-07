/**
 *******************************************************************************
 * @file    motor_control.h
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Interface pour le contrôle des moteurs
 *******************************************************************************
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <stdbool.h>
#include <stdint.h>

// Initialisation des moteurs
bool init_motors(void);

void set_pwm_pulse(uint16_t pulse);

// Contrôle de la vitesse du moteur gauche
void set_left_motor_speed(uint8_t speed);

// Contrôle de la vitesse du moteur droit
void set_right_motor_speed(uint8_t speed);

// Arrêt des deux moteurs
void stop_motors(void);

#endif /* MOTOR_CONTROL_H_ */
