// /**
//  *******************************************************************************
//  * @file    motor_control.c
//  * @author  Drone_1_Axe Team
//  * @date    Avril 23, 2025
//  * @brief   Implémentation simplifiée pour générer un PWM sur PA12
//  *******************************************************************************
//  */

// #include "motor_control.h"
// #include "stm32g4_gpio.h"
// #include "stm32g4_timer.h"
// #include <stdio.h>

// // Constantes pour l'ESC Skywalker V2
// // Selon les spécifications de Skywalker V2, le signal est standard entre 1100us et 1940us
// #define ESC_PWM_FREQUENCY_HZ 250     // Résultat de période de 4ms comme demandé par le prof
// #define ESC_PWM_PERIOD_US    4000    // 4ms = 250Hz

// // Valeurs PWM pour l'ESC Skywalker (en pourcentage de 0-1000)
// #define ESC_MIN_PULSE           275     // 1100us/4000us = 27.5% (position arrêt)
// #define ESC_NEUTRAL_PULSE       300     // Position neutre ~1200us/4000us 30.0%
// #define ESC_MAX_PULSE           485     // 1940us/4000us = 48.5% (plein gaz)

// // Valeurs PWM pour l'ESC Skywalker (pour le test)
// #define ESC_MAX_PULSE_TEST      300     // plein gaz (pour le test)
// #define ESC_NEUTRAL_PULSE_TEST  288     // Position neutre (pour le test)


// // Fonction d'initialisation des moteurs pour l'ESC Skywalker V2
// bool init_motors(void) {
//     printf("Initialisation ESC Skywalker V2 pour moteur A2212/6T...\r\n");

//     // 1. Configuration du timer 4 (période de 4ms = 250Hz)
//     BSP_TIMER_run_us(TIMER4_ID, ESC_PWM_PERIOD_US, false);

//     // 2. Configuration de la broche PA12 en mode PWM avec le timer 4 canal 2
//     // Commencer avec position throttle à zéro (ESC_MIN_PULSE)
//     BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE, false, false);

//     // 3. Séquence de calibration du ESC (throttle range)
//     printf("Démarrage de la séquence d'initialisation de l'ESC...\r\n");

//     // Position gaz au maximum pour calibration (comme indiqué dans la datasheet)
//     printf("Position throttle maximum...\r\n");
//     BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MAX_PULSE);

//     // Attente de connexion de la batterie (ou simuler cette attente)
//     HAL_Delay(3000);  // Attente pour que l'utilisateur ait le temps de connecter la batterie

//     // Position gaz au minimum
//     printf("Position throttle minimum...\r\n");
//     BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE);

//     // Attente pour que l'ESC reconnaisse la position minimum et termine la calibration
//     HAL_Delay(2000);

//     printf("Calibration terminée - Vérifiez les beeps de confirmation\r\n");
//     printf("PWM configuré: Fréquence=%dHz, Période=%dus\r\n", ESC_PWM_FREQUENCY_HZ, ESC_PWM_PERIOD_US);
//     printf("Plage PWM: Min=%d, Neutre=%d, Max=%d (sur 1000)\r\n", ESC_MIN_PULSE, ESC_NEUTRAL_PULSE, ESC_MAX_PULSE);

//     set_pwm_pulse(ESC_MAX_PULSE);
//     printf("Position throttle maximum...\r\n");
//     HAL_Delay(5000);  // Attente pour que l'utilisateur puisse voir le signal

//     set_pwm_pulse(ESC_MIN_PULSE);
//     printf("Position throttle minimum...\r\n");
//     HAL_Delay(5000);  // Attente pour que l'utilisateur puisse voir le signal

//     set_pwm_pulse(ESC_NEUTRAL_PULSE);
//     printf("Position throttle neutre...\r\n");
//     HAL_Delay(5000);  // Attente pour que l'utilisateur puisse voir le signal

//     set_pwm_pulse(ESC_MIN_PULSE);
//     printf("Position throttle minimum...\r\n");

//     printf("Moteurs prêts à l'emploi\r\n");
//     return true;
// }

// // Contrôle direct de la valeur PWM (0-1000)
// void set_pwm_pulse(uint16_t pulse) {
//     // Limiter les valeurs entre MIN et MAX
//     if (pulse < ESC_MIN_PULSE) 
//         pulse = ESC_MIN_PULSE;
//     else if (pulse > ESC_MAX_PULSE)
//         pulse = ESC_MAX_PULSE;

//     BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, pulse);
// }

// // Contrôle de la vitesse du moteur gauche
// void set_left_motor_speed(uint8_t speed) {
//     // Conversion de la vitesse (0-255) en valeur PWM (ESC_MIN_PULSE à ESC_MAX_PULSE)
//     uint16_t pulse;

//     if (speed == 0) {
//         // Signal d'arrêt
//         pulse = ESC_MIN_PULSE;
//     } else {
//         // Conversion linéaire de 0-255 vers ESC_MIN_PULSE-ESC_MAX_PULSE
//         pulse = ESC_MIN_PULSE + ((uint32_t)speed * (ESC_MAX_PULSE - ESC_MIN_PULSE)) / 255;
//     }

//     set_pwm_pulse(pulse);
// }

// // Contrôle de la vitesse du moteur droit - non utilisé dans le drone 1 axe
// void set_right_motor_speed(uint8_t speed) {
//     (void)speed; // Éviter l'avertissement de variable non utilisée
// }

// // Arrêt des moteurs
// void stop_motors(void) {
//     // Arrêt = position minimale du throttle
//     set_pwm_pulse(ESC_MIN_PULSE);
//     printf("Moteurs arrêtés\r\n");
// }








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


/**
 * @brief Procédure de calibration de la plage de throttle
 * @note Cette fonction doit être appelée lors de la première utilisation ou lors du changement d'émetteur
 * @note Implémentée selon la section "ESC/Radio Calibration" de la datasheet
 */
void esc_throttle_range_calibration(uint16_t min, uint16_t max) {
    // 1. Throttle → max (1940 µs → 48,5 %)
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MAX_PULSE);
    // Attendre 2 s pour être sûr de capter les deux bips courts ◆ minimum requis pour l’ESC  
    HAL_Delay(2000);

    // 2. Throttle min (1100 µs → 27,5 %)
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE);
    // Attendre 1 s pour l’acceptation du point min  
    HAL_Delay(1000);

    // Calibration terminée !
    printf("Calibration terminée.\r\n");
}

/**
 * @brief Procédure de démarrage normal
 * @note Implémentée selon la section "Normal Start-up Process" de la datasheet
 */
void esc_normal_startup(void) {
    printf("\n\n\nDémarrage de l'ESC...\r\n");

    printf("\n\nPosition throttle minimum\r\n");
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE);

    printf("\n\nSignal sonore\r\n");
    HAL_Delay(3000);

    printf("\n\nL'ESC émet plusieurs beeps indiquant le nombre de cellules LiPo\r\n");
    HAL_Delay(1000);

    printf("\n\nLong beep de confirmation...\r\n");
    HAL_Delay(1000);

    printf("\n\nESC prêt\r\n");
    printf("\n\nLes 4 beeps que vous entendez sont le cutoff threshold (par défaut: Medium)\r\n");
    printf("\n\nLe beep final indique le mode de frein (par défaut: Disabled)\r\n");
}

/**
 * @brief Initialisation des moteurs
 */
bool init_motors(void) {
    printf("\n\n\nInitialisation ESC Skywalker V2 pour moteur A2212/6T...\r\n");

    // 1. Configuration du timer 4 (période de 4ms = 250Hz)
    BSP_TIMER_run_us(TIMER4_ID, ESC_PWM_PERIOD_US, false);

    // 2. Configuration de la broche PA12 en mode PWM avec le timer 4 canal 2
    BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, ESC_MIN_PULSE, false, false);

    test_motors();

    return true;
}

void test_motors(void) {
    // Test des moteurs
    printf("\n\n\nTest des moteurs...\r\n");

    esc_throttle_range_calibration(ESC_MIN_PULSE, ESC_MAX_PULSE);
    esc_normal_startup();

    // Position gaz au minimum
    set_pwm_pulse(ESC_MIN_PULSE);
    printf("Position throttle minimum...\r\n");
    HAL_Delay(1000);  // Attente pour que l'utilisateur puisse voir le signal

    stop_motors();
    HAL_Delay(2000);

    // Position gaz au maximum
    set_pwm_pulse(ESC_MAX_PULSE);
    printf("Position throttle maximum...\r\n");
    HAL_Delay(1000);  // Attente pour que l'utilisateur puisse voir le signal

    stop_motors();
    HAL_Delay(2000);

    // Position gaz au minimum
    set_pwm_pulse(ESC_MIN_PULSE);
    printf("Position throttle minimum...\r\n");
    HAL_Delay(1000);  // Attente pour que l'utilisateur puisse voir le signal


    // Arrêt des moteurs
    stop_motors();
}

// Contrôle direct de la valeur PWM (0-1000)
void set_pwm_pulse(uint16_t pulse) {
    // Limiter les valeurs entre MIN et MAX
    if (pulse < ESC_MIN_PULSE) {
        pulse = ESC_MIN_PULSE;
    }
    else if (pulse > ESC_MAX_PULSE) {
        pulse = ESC_MAX_PULSE;
    }

    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, pulse);
}

// Contrôle de la vitesse du moteur gauche
void set_left_motor_speed(uint8_t speed) {
    // Conversion de la vitesse (0-255) en valeur PWM (ESC_MIN_PULSE à ESC_MAX_PULSE)
    uint16_t pulse;

    if (speed == 0) {
        // Signal d'arrêt
        pulse = ESC_MIN_PULSE;
    }
    else {
        // Conversion linéaire de 0-255 vers ESC_MIN_PULSE-ESC_MAX_PULSE
        // On divise d'abord par 255 pour éviter les problèmes d'overflow
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
