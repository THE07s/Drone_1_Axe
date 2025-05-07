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
TIM_HandleTypeDef htim4;  // Handler pour le timer 4 (au lieu de timer 2)
uint16_t min_pulse = 1000;  // Largeur d'impulsion minimale (1 ms)
uint16_t max_pulse = 2000;  // Largeur d'impulsion maximale (2 ms)

bool init_pwm(void) {
    // Configuration du GPIO pour la sortie PWM - PA12 mappé sur TIM4_CH2
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF10_TIM4);

    // timer TIM4 pour PWM (au lieu de TIM2)
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 79;  // Divise l'horloge de 80Mhz pour avoir 1Mhz
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 20000 - 1;  // Période de 20 ms (1 MHz / 20000 = 50 Hz)
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK) {
        printf("Erreur d'initialisation du timer PWM\r\n");
        return false;  // Erreur d'initialisation
    }

    // Configuration du canal PWM (canal 2 au lieu de canal 1)
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = min_pulse;  // Largeur d'impulsion de 1 ms (1 MHz * 1 ms = 1000)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
        printf("Erreur de configuration du canal PWM\r\n");
        return false;  // Erreur de configuration du canal
    }

    // Démarrage du PWM sur le canal 2
    if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2) != HAL_OK) {
        printf("Erreur de démarrage du PWM\r\n");
        return false;  // Erreur de démarrage du PWM
    }

    printf("Initialisation du PWM réussie\r\n");
    return true;  // PWM initialisé avec succès
}

// Fonction pour modifier la largeur d'impulsion du PWM
void set_pwm_pulse(uint16_t pulse) {
    // Met à jour la largeur d'impulsion (en ticks)
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pulse);
}

// Initialisation des moteurs
bool init_motors(void) {
    bool status = true;
    printf("Test d'initialisation des moteurs...\r\n");
    
    // Initialisation du PWM pour le contrôle des moteurs
    if (!init_pwm()) {
        printf("Échec de l'initialisation du PWM\r\n");
        return false;
    }
    
    // Séquence d'armement standard pour ESC brushless
    printf("Séquence d'armement de l'ESC...\r\n");
    
    // 1. Signal d'arrêt initial pendant 2 secondes
    printf("Étape 1: Signal d'arrêt initial (1000µs)...\r\n");
    set_pwm_pulse(min_pulse);
    HAL_Delay(2000);
    
    // 2. Signal plein gaz pendant 2 secondes (certains ESC ont besoin de cette étape)
    printf("Étape 2: Signal plein gaz (2000µs)...\r\n");
    set_pwm_pulse(max_pulse);
    HAL_Delay(2000);
    
    // 3. Signal d'arrêt pendant 2 secondes pour confirmer l'armement
    printf("Étape 3: Signal d'arrêt final (1000µs)...\r\n");
    set_pwm_pulse(min_pulse);
    HAL_Delay(2000);
    
    printf("ESC armé!\r\n");
    
    // 4. Test de rampe lente - démarre lentement et monte plus haut
    printf("Test de rampe de vitesse...\r\n");
    // Augmentation progressive de la largeur d'impulsion - monte jusqu'à 1400μs
    for (uint16_t pulse = min_pulse; pulse < min_pulse + 400; pulse += 20) {
        set_pwm_pulse(pulse);
        printf("Pulse: %d µs\r\n", pulse);
        HAL_Delay(200);  // Attente plus longue entre chaque augmentation
    }
    
    // 5. Retour à la position d'arrêt
    printf("Retour à la position d'arrêt...\r\n");
    set_pwm_pulse(min_pulse);
    HAL_Delay(1000);
    
    printf("Test des moteurs terminé\r\n");
    return status;
}

// Contrôle de la vitesse du moteur gauche
void set_left_motor_speed(uint8_t speed) {
    // Conversion de la plage 0-255 à la plage min_pulse-max_pulse
    uint16_t pulse = min_pulse + ((uint32_t)speed * (max_pulse - min_pulse)) / 255;
    set_pwm_pulse(pulse);
    printf("Vitesse moteur gauche: %d (%d µs)\r\n", speed, pulse);
}

// Contrôle de la vitesse du moteur droit
void set_right_motor_speed(uint8_t speed) {
    // Note: Cette fonction pourra être implémentée dans le futur avec TIM4_CH1
    // Code de contrôle du moteur droit à compléter
    printf("Vitesse moteur droit: %d\r\n", speed);
}

// Arrêt des deux moteurs
void stop_motors(void) {
    printf("Arrêt des moteurs\r\n");
    set_pwm_pulse(min_pulse);
}
