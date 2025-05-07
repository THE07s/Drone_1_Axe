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
TIM_HandleTypeDef htim2;  // Handler global pour le timer PWM
uint16_t min_pulse = 1000;  // Largeur d'impulsion minimale (1 ms)
uint16_t max_pulse = 2000;  // Largeur d'impulsion maximale (2 ms)

bool init_pwm(void) {
    // Configuration du GPIO pour la sortie PWM
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);

    // timer TIM2 pour PWM
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;  // Divise l'horloge de 80Mhz pour avoir 1Mhz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 20000 - 1;  // Période de 20 ms (1 MHz / 20000 = 50 Hz)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        printf("Erreur d'initialisation du timer PWM\r\n");
        return false;  // Erreur d'initialisation
    }

    // Configuration du canal PWM (canal 1)
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = min_pulse;  // Largeur d'impulsion de 1 ms (1 MHz * 1 ms = 1000)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        printf("Erreur de configuration du canal PWM\r\n");
        return false;  // Erreur de configuration du canal
    }

    // Démarrage du PWM sur le canal 1
    if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK) {
        printf("Erreur de démarrage du PWM\r\n");
        return false;  // Erreur de démarrage du PWM
    }

    printf("Initialisation du PWM réussie\r\n");
    return true;  // PWM initialisé avec succès
}

// Fonction pour modifier la largeur d'impulsion du PWM
void set_pwm_pulse(uint16_t pulse) {
    // Met à jour la largeur d'impulsion (en ticks)
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse);
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
    
    // Test de fonctionnement du moteur - séquence de démarrage sécurisée
    printf("Test de la séquence de démarrage des ESC...\r\n");
    
    // 1. Signal d'arrêt (1000µs) pendant 2 secondes
    printf("Envoi du signal d'arrêt (1000µs)...\r\n");
    set_pwm_pulse(min_pulse);
    HAL_Delay(2000);
    
    // 2. Test de rampe lente (optionnel) - démarre lentement et s'arrête
    printf("Test de rampe lente...\r\n");
    // Augmentation progressive de la largeur d'impulsion
    for (uint16_t pulse = min_pulse; pulse < min_pulse + 200; pulse += 10) {
        set_pwm_pulse(pulse);
        printf("Pulse: %d µs\r\n", pulse);
        HAL_Delay(100);  // Attente de 100ms entre chaque augmentation
    }
    
    // 3. Retour à la position d'arrêt
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
    // Code de contrôle du moteur droit à compléter
    // Note: Dans un drone 1 axe, il peut n'y avoir qu'un seul moteur
    printf("Vitesse moteur droit: %d\r\n", speed);
}

// Arrêt des deux moteurs
void stop_motors(void) {
    printf("Arrêt des moteurs\r\n");
    set_pwm_pulse(min_pulse);
}
