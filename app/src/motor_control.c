/**
 * @file motor_control.c
 * @brief Implémentation du module de contrôle des moteurs via ESC
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#include "stm32g4xx_hal.h"
#include "stm32g4_timer.h"
#include "motor_control.h"
#include "state.h"

void configure_timer_pwm(void) {
    BSP_TIMER_run_us(TIMER4_ID, PERIODE_PWM_US, false);
    
#if USE_MOTOR1
    BSP_TIMER_enable_PWM(TIMER4_ID, ESC_1, ESC_PULSE_MIN, false, false);
#endif

#if USE_MOTOR2
    BSP_TIMER_enable_PWM(TIMER4_ID, ESC_2, ESC_PULSE_MIN, false, false);
#endif
}

void set_impulsion(uint8_t moteur, uint16_t pulse) {
    if (pulse < ESC_PULSE_MIN)  pulse = ESC_PULSE_MIN;
    if (pulse > ESC_PULSE_MAX)  pulse = ESC_PULSE_MAX;
    
#if USE_MOTOR1
    if (moteur == 1) {
        BSP_TIMER_set_duty(TIMER4_ID, ESC_1, pulse);
    }
#endif

#if USE_MOTOR2
    if (moteur == 2) {
        BSP_TIMER_set_duty(TIMER4_ID, ESC_2, pulse);
    }
#endif
}

void arreter_moteur(uint8_t moteur) {
    set_impulsion(moteur, ESC_PULSE_MIN);
    
#if USE_MOTOR1
    if (moteur == 1) g_state.statut_moteur1 = 0;
#endif

#if USE_MOTOR2
    if (moteur == 2) g_state.statut_moteur2 = 0;
#endif
}

void set_moteur(uint8_t moteur, uint16_t pulse) {
    set_impulsion(moteur, pulse);
    
#if USE_MOTOR1
    if (moteur == 1) g_state.statut_moteur1 = 1;
#endif

#if USE_MOTOR2
    if (moteur == 2) g_state.statut_moteur2 = 1;
#endif
}

void init_motors(void) {
    configure_timer_pwm();
    
#if USE_MOTOR1
    set_moteur(1, ESC_PULSE_MIN);
#endif

#if USE_MOTOR2    
    set_moteur(2, ESC_PULSE_MIN);
#endif

    HAL_Delay(3000);

#if DEBUG_MOTORS
    printf("Début des cycles de test des moteurs...\r\n");

    // Premier cycle de calibration
    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
#if USE_MOTOR1
        set_impulsion(1, pulse);
#endif
#if USE_MOTOR2
        set_impulsion(2, pulse);
#endif
        HAL_Delay(1);
    }

#if USE_MOTOR1
    arreter_moteur(1);
#endif
#if USE_MOTOR2
    arreter_moteur(2);
#endif

    // Deuxième cycle de calibration
    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
#if USE_MOTOR1
        set_impulsion(1, pulse);
#endif
#if USE_MOTOR2
        set_impulsion(2, pulse);
#endif
        HAL_Delay(1);
    }

#if USE_MOTOR1
    arreter_moteur(1);
#endif
#if USE_MOTOR2
    arreter_moteur(2);
#endif

    // Troisième cycle de calibration
    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
#if USE_MOTOR1
        set_impulsion(1, pulse);
#endif
#if USE_MOTOR2
        set_impulsion(2, pulse);
#endif
        HAL_Delay(1);
    }

#if USE_MOTOR1
    arreter_moteur(1);
#endif
#if USE_MOTOR2
    arreter_moteur(2);
#endif

    printf("Initialisation terminée.\r\n");
#endif
}
