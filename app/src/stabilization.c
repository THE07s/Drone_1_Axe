/**
 *******************************************************************************
 * @file    stabilization.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'algorithme de stabilisation
 *******************************************************************************
 */

#include "stabilization.h"
#include "motor_control.h"
#include <stdio.h>

// Variables globales
static bool stabilization_enabled = false;

// Initialisation du système de stabilisation
void init_stabilization(void) {
    // Code d'initialisation à compléter
    stabilization_enabled = false;
}

// Activer la stabilisation automatique
void enable_stabilization(void) {
    stabilization_enabled = true;
    printf("Stabilisation activée\r\n");
}

// Désactiver la stabilisation automatique
void disable_stabilization(void) {
    stabilization_enabled = false;
    printf("Stabilisation désactivée\r\n");
}

// Calculer les corrections de vitesse des moteurs selon l'angle
void process_stabilization(float angle) {
    // Code de l'algorithme de stabilisation à compléter
    // (utilisation potentielle d'un contrôleur PID)
}