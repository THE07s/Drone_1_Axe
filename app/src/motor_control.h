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

/**
 * @brief Procédure de calibration de la plage de throttle
 * @note Cette fonction doit être appelée lors de la première utilisation ou lors du changement d'émetteur
 * @note Implémentée selon la section "ESC/Radio Calibration" de la datasheet
 */
void esc_throttle_range_calibration(void);

/**
 * @brief Procédure de démarrage normal
 * @note Implémentée selon la section "Normal Start-up Process" de la datasheet
 */
void esc_normal_startup(void);

/**
 * @brief Initialisation des moteurs
 * @return true si l'initialisation est réussie, false sinon
 */
bool init_motors(void);

/**
 * @brief Contrôle direct de la valeur PWM (0-1000)
 * @param pulse Valeur PWM entre 0 et 1000 (sera limitée aux valeurs min et max de l'ESC)
 */
void set_pwm_pulse(uint16_t pulse);

/**
 * @brief Contrôle de la vitesse du moteur gauche
 * @param speed Vitesse entre 0 (arrêt) et 255 (pleine puissance)
 */
void set_left_motor_speed(uint8_t speed);

/**
 * @brief Contrôle de la vitesse du moteur droit
 * @param speed Vitesse entre 0 (arrêt) et 255 (pleine puissance)
 */
void set_right_motor_speed(uint8_t speed);

/**
 * @brief Arrêt des deux moteurs
 */
void stop_motors(void);

#endif /* MOTOR_CONTROL_H_ */
