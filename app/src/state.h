#ifndef STATE_H_
#define STATE_H_

#include <stdbool.h>

typedef struct {
    float angle_MPU1;
    float angle_MPU2;
    float command_position;
    float asservissement_value;
    int statut_moteur1;
    int statut_moteur2;
    bool system_ok;
} SystemState;

extern SystemState g_state;

#endif /* STATE_H_ */
