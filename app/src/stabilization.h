/**
 * @file stabilization.h
 * @brief Module d'asservissement et de stabilisation via un correcteur proportionnel
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef STABILIZATION_H_
#define STABILIZATION_H_

#include "motor_control.h"
#include "state.h"

/**
 * @brief Traite la stabilisation du drone
 * 
 * Calcule la correction nécessaire pour stabiliser le drone en comparant
 * l'angle actuel du système avec l'angle de commande désiré. Dont il va tirer l'erreur.
 * Utilise un correcteur proportionnel pour générer les signaux de commande des moteurs.
 * 
 * @param angle_system Angle actuel du système en degrés
 * @param angle_commande Angle de consigne désiré en degrés
 * 
 * @pre Les moteurs et les capteurs doivent être initialisés
 * @post Les moteurs sont commandés selon la correction calculée
 * @post La valeur d'asservissement est mise à jour dans g_state
 */
void process_stabilization(float angle_system, float angle_commande);

#endif /* STABILIZATION_H_ */