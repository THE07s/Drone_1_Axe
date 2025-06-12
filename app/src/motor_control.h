#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

// Constantes ESC
#define PERIODE_PWM_US  4000   // 4 000 µs → 250 Hz
#define ESC_PULSE_MIN   275    // 1100 µs / 4000 µs = 27,5 %
#define ESC_PULSE_MAX   485    // 1940 µs / 4000 µs = 48,5 %
// #define ESC_PULSE_MAX   ESC_PULSE_MIN + 26    // max "safe"

// Def Timer pour ESC
#define ESC_1   TIM_CHANNEL_2   // PA12/CH2
#define ESC_2   TIM_CHANNEL_1   // PB6/CH1

bool init_motors(void);
void configure_timer_pwm(void);
void set_impulsion(uint8_t moteur, uint16_t pulse);
void set_moteur(uint8_t moteur, uint16_t pulse);
void arreter_moteur(uint8_t moteur);

#endif