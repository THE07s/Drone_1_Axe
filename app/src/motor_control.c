/**
 *******************************************************************************
 * @file    motor_control.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation simplifiée pour générer un PWM sur PA12
 *******************************************************************************
 */

#include "motor_control.h"
#include "stm32g4_gpio.h"
#include "stm32g4_timer.h"
#include <stdio.h>

// Constantes pour l'ESC Skywalker V2
// Selon les spécifications de Skywalker V2, le signal est standard entre 1100us et 1940us
#define ESC_PWM_FREQUENCY_HZ 250     // Résultat de période de 4ms comme demandé par le prof
#define ESC_PWM_PERIOD_US    4000    // 4ms = 250Hz

// Valeurs PWM pour l'ESC Skywalker (en pourcentage de 0-1000)
#define ESC_MIN_PULSE        275     // 1100us/4000us = 27.5% (position arrêt)
#define ESC_MAX_PULSE        485     // 1940us/4000us = 48.5% (plein gaz)
#define ESC_NEUTRAL_PULSE    300     // Position neutre ~1200us/4000us

// Variable pour indiquer si la calibration a été effectuée
static bool throttle_calibrated = false;

/**
 * @brief Procédure de calibration de la plage de throttle
 * @note Cette fonction doit être appelée lors de la première utilisation ou lors du changement d'émetteur
 * @note Implémentée selon la section "ESC/Radio Calibration" de la datasheet
 */
void esc_throttle_range_calibration(void) {
    printf("Démarrage de la procédure de calibration du throttle...\r\n");
    
    // Étape 1: Mettre le throttle à la position maximale
    printf("1. Position throttle maximum\r\n");
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MAX_PULSE);
    
    // Étape 2: Connecter la batterie
    printf("2. Connectez la batterie à l'ESC maintenant\r\n");
    printf("   Attendez le signal sonore \"♪123\" puis deux beeps courts\r\n");
    HAL_Delay(5000); // Attendre que l'utilisateur connecte la batterie
    
    // Étape 3: Dans les 5 secondes après les 2 beeps, mettre le throttle à la position minimale
    printf("3. Position throttle minimum\r\n");
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE);
    
    // Étape 4: Attendre le signal sonore confirmant la calibration complète
    printf("4. Attente du beep long de confirmation...\r\n");
    HAL_Delay(2000);
    
    printf("Calibration de la plage de throttle terminée!\r\n");
    throttle_calibrated = true;
}

/**
 * @brief Procédure de démarrage normal
 * @note Implémentée selon la section "Normal Start-up Process" de la datasheet
 */
void esc_normal_startup(void) {
    printf("Démarrage de la procédure normale de l'ESC...\r\n");
    
    // Étape 1: S'assurer que le throttle est à la position minimale
    printf("1. Position throttle minimum\r\n");
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE);
    
    // Étape 2: Connecter la batterie à l'ESC
    printf("2. Connectez la batterie à l'ESC\r\n");
    printf("   Attendez le signal sonore \"♪123\"\r\n");
    HAL_Delay(3000); // Attendre que l'utilisateur connecte la batterie
    
    // Étape 3: Attendre les beeps indiquant le nombre de cellules LiPo
    printf("3. L'ESC émet plusieurs beeps indiquant le nombre de cellules LiPo\r\n");
    HAL_Delay(1000);
    
    // Étape 4: Attendre le beep long indiquant que l'ESC est prêt
    printf("4. Attente du beep long de démarrage...\r\n");
    HAL_Delay(1000);
    
    printf("ESC prêt à fonctionner!\r\n");
    printf("Les 4 beeps que vous entendez sont le cutoff threshold (par défaut: Medium)\r\n");
    printf("Le beep final indique le mode de frein (par défaut: Disabled)\r\n");
}

/**
 * @brief Initialisation des moteurs
 */
bool init_motors(void) {
    printf("Initialisation ESC Skywalker V2 pour moteur A2212/6T...\r\n");
    printf("Timing recommandé: Low (5°) pour le moteur A2212/6T\r\n");
    
    // 1. Configuration du timer 4 (période de 4ms = 250Hz)
    BSP_TIMER_run_us(TIMER4_ID, ESC_PWM_PERIOD_US, false);
    
    // 2. Configuration de la broche PA12 en mode PWM avec le timer 4 canal 2
    BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE, false, false);
    
    // 3. Demander à l'utilisateur s'il souhaite calibrer ou démarrer normalement
    printf("\r\n*****************************************\r\n");
    printf("Vous pouvez maintenant:\r\n");
    printf("1. Effectuer la calibration du throttle range\r\n");
    printf("   Dans ce cas, NE CONNECTEZ PAS encore la batterie à l'ESC\r\n");
    printf("2. Procéder au démarrage normal\r\n");
    printf("   Dans ce cas, assurez-vous que le throttle est au minimum\r\n");
    printf("*****************************************\r\n\n");
    
    // Par défaut, nous utilisons la procédure de démarrage normal
    esc_normal_startup();
    
    return true;
}

// Contrôle direct de la valeur PWM (0-1000)
void set_pwm_pulse(uint16_t pulse) {
    // Limiter les valeurs entre MIN et MAX
    if (pulse < ESC_MIN_PULSE) 
        pulse = ESC_MIN_PULSE;
    else if (pulse > ESC_MAX_PULSE)
        pulse = ESC_MAX_PULSE;
    
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, pulse);
}

// Contrôle de la vitesse du moteur gauche
void set_left_motor_speed(uint8_t speed) {
    // Conversion de la vitesse (0-255) en valeur PWM (ESC_MIN_PULSE à ESC_MAX_PULSE)
    uint16_t pulse;
    
    if (speed == 0) {
        // Signal d'arrêt
        pulse = ESC_MIN_PULSE;
    } else {
        // Conversion linéaire de 0-255 vers ESC_MIN_PULSE-ESC_MAX_PULSE
        pulse = ESC_MIN_PULSE + ((uint32_t)speed * (ESC_MAX_PULSE - ESC_MIN_PULSE)) / 255;
    }
    
    set_pwm_pulse(pulse);
}

// Contrôle de la vitesse du moteur droit - non utilisé dans le drone 1 axe
void set_right_motor_speed(uint8_t speed) {
    (void)speed; // Éviter l'avertissement de variable non utilisée
}

// Arrêt des moteurs
void stop_motors(void) {
    // Arrêt = position minimale du throttle
    set_pwm_pulse(ESC_MIN_PULSE);
    printf("Moteurs arrêtés\r\n");
}