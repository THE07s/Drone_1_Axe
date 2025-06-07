/**
 *******************************************************************************
 * @file    stabilization.h
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Interface pour l'algorithme de stabilisation
 *******************************************************************************
 */

#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include <stdbool.h>

// Initialisation du système de stabilisation
void init_stabilization(void);

// Activer la stabilisation automatique
void enable_stabilization(void);

// Désactiver la stabilisation automatique
void disable_stabilization(void);

// Calculer les corrections de vitesse des moteurs selon l'angle
void process_stabilization(float angle_system, float angle_commande);

#endif /* STABILIZATION_H_ */