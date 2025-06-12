#include "stm32g4xx_hal.h"
#include "stm32g4_timer.h"
#include "motor_control.h"
#include "state.h"

void configure_timer_pwm(void) {
    BSP_TIMER_run_us(TIMER4_ID, PERIODE_PWM_US, false);
    BSP_TIMER_enable_PWM(TIMER4_ID, ESC_1, ESC_PULSE_MIN, false, false);
    BSP_TIMER_enable_PWM(TIMER4_ID, ESC_2, ESC_PULSE_MIN, false, false);
}

void set_impulsion(uint8_t moteur, uint16_t pulse) {
    if (pulse < ESC_PULSE_MIN)  pulse = ESC_PULSE_MIN;
    if (pulse > ESC_PULSE_MAX)  pulse = ESC_PULSE_MAX;
    if (moteur == 1) {
        BSP_TIMER_set_duty(TIMER4_ID, ESC_1, pulse);
    } else if (moteur == 2) {
        BSP_TIMER_set_duty(TIMER4_ID, ESC_2, pulse);
    }
}

void arreter_moteur(uint8_t moteur) {
    set_impulsion(moteur, ESC_PULSE_MIN);
    if (moteur == 1) g_state.statut_moteur1 = 0;
    if (moteur == 2) g_state.statut_moteur2 = 0;
}

void set_moteur(uint8_t moteur, uint16_t pulse) {
    set_impulsion(moteur, pulse);
    if (moteur == 1) g_state.statut_moteur1 = 1;
    if (moteur == 2) g_state.statut_moteur2 = 1;
}

bool init_motors(void) {
    configure_timer_pwm();
    set_moteur(1, ESC_PULSE_MIN);
    set_moteur(2, ESC_PULSE_MIN);
    HAL_Delay(3000);
    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
        set_impulsion(1, pulse);
        set_impulsion(2, pulse);
        HAL_Delay(1);
    }

    arreter_moteur(1);
    arreter_moteur(2);

    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
        set_impulsion(1, pulse);
        set_impulsion(2, pulse);
        HAL_Delay(1);
    }

    arreter_moteur(1);
    arreter_moteur(2);

    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
        set_impulsion(1, pulse);
        set_impulsion(2, pulse);
        HAL_Delay(1);
    }

    arreter_moteur(1);
    arreter_moteur(2);

    return true;
}
