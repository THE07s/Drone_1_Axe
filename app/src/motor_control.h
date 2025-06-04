// --------------------------------------------------
// Exemple de fichier d'en-tête associé : motor_control_simple.h
// --------------------------------------------------

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

bool init_motors(void);
void configure_timer_pwm(void);
void changer_impulsion(uint16_t pulse);

#endif // MOTOR_CONTROL_H