/**
 * @file state.h
 * @brief Structure de données qui enregistre l'état du système
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdbool.h>

/**
 * @brief Structure contenant l'état global du système
 */
typedef struct {
    float angle_MPU1;           /*!< Angle mesuré par le premier MPU6050 (système) */
    float command_position;     /*!< Angle mesuré par le second MPU6050 */
    float asservissement_value; /*!< Valeur de correction de l'asservissement */
    int statut_moteur1;         /*!< Statut du moteur 1 (0=arrêté, 1=en marche) */
    int statut_moteur2;         /*!< Statut du moteur 2 (0=arrêté, 1=en marche) */
    bool system_ok;             /*!< État général du système (true=OK, false=erreur) */
} SystemState;

/**
 * @brief Variable globale contenant l'état du système
 */
extern SystemState g_state;

#endif /* STATE_H_ */
