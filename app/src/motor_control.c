#include "stm32g4xx_hal.h"     // HAL_TIM_PWM_Start, HAL_Delay, etc.
#include "stm32g4_timer.h"     // BSP_TIMER_run_us, BSP_TIMER_enable_PWM, BSP_TIMER_set_duty

#define PERIODE_PWM_US  4000U   // 4 000 µs → 250 Hz
#define ESC_PULSE_MIN   275U    // 1100 µs / 4000 µs = 27,5 % → valeur 275/1000
#define ESC_PULSE_MAX   485U    // 1940 µs / 4000 µs = 48,5 % → valeur 485/1000

void configure_timer_pwm(void) {
    // Configure TIM4 pour 250 Hz et active directement le PWM sur PA12/CH2
    BSP_TIMER_run_us(TIMER4_ID, PERIODE_PWM_US, false);
    BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_2, ESC_PULSE_MIN, false, false);
}

void set_impulsion(uint16_t pulse) {
    if (pulse < ESC_PULSE_MIN)  pulse = ESC_PULSE_MIN;
    if (pulse > ESC_PULSE_MAX)  pulse = ESC_PULSE_MAX;
    BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_2, pulse);
}

bool init_motors(void) {
    configure_timer_pwm();
    set_impulsion(ESC_PULSE_MIN);      // Gaz minimum au démarrage
    HAL_Delay(3000);                       // Attendre les bips d'initialisation

    // Augmente progressivement la largeur d'impulsion jusqu'au ralenti
    for (uint16_t pulse = ESC_PULSE_MIN; pulse <= ESC_PULSE_MAX; pulse += 1) {
        set_impulsion(pulse);
        HAL_Delay(20);
    }
    for (uint16_t pulse = ESC_PULSE_MAX; pulse >= ESC_PULSE_MIN; pulse -= 1) {
        set_impulsion(pulse);
        HAL_Delay(20);
    }
    set_impulsion(ESC_PULSE_MIN); // Ralenti final
    return true;
}