// --------------------------------------------------
// Exemple de fichier d'en-tête associé : motor_control_simple.h
// --------------------------------------------------

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

bool init_motors(void);
void configure_timer_pwm(void);
void set_impulsion(uint8_t moteur, uint16_t pulse);
void set_moteur(uint8_t moteur, uint16_t pulse);
void arreter_moteur(uint8_t moteur);

#endif // MOTOR_CONTROL_H