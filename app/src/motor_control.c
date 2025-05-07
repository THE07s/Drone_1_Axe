/**
 *******************************************************************************
 * @file    motor_control.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour le contrôle des moteurs
 *******************************************************************************
 */

#include "motor_control.h"
#include "stm32g4_gpio.h"
#include "stm32g4_timer.h"
#include <stdio.h>

// Variables globales
// À définir selon la configuration matérielle

bool init_pwm(void) {
    // Configuration du GPIO pour la sortie PWM
    BSP_GPIO_PinCfg(GPIOA, GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);

    // timer TIM2 pour PWM
    TIM_HandleTypeDef htim2;
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;  // Divise l'horloge de 80Mhz pour avoir 1Mhz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 20000 - 1;  // P�riode de 20 ms (1 MHz / 20000 = 50 Hz)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        return false;  // Erreur d'initialisation
    }

    // Configuration du canal PWM (canal 1)
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1000;  // Largeur d'impulsion de 1 ms (1 MHz * 1 ms = 1000)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        return false;  // Erreur de configuration du canal
    }

    // D�marrage du PWM sur le canal 1
    if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK) {
        return false;  // Erreur de d�marrage du PWM
    }

    return true;  // PWM initialis� avec succ�s
}

// Fonction pour modifier la largeur d'impulsion du PWM
void set_pwm_pulse(uint16_t pulse) {
    // Met à jour la largeur d'impulsion (en ticks)
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse);
}



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
