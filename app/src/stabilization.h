#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include <stdbool.h>
#include "motor_control.h"
#include "state.h"
#include <math.h>


void process_stabilization(float angle_system, float angle_commande);

#endif /* STABILIZATION_H_ */