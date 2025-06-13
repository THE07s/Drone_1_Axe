/**
 * @file sensors.h
 * @brief Module de gestion des capteurs MPU6050
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdbool.h>
#include <stdint.h>
#include "MPU6050/stm32g4_mpu6050.h"
#include "state.h"

/**
 * @brief Structure pour stocker les données des capteurs
 */
typedef struct {
    float accel_x;      /*!< Accélération selon X */
    float accel_y;      /*!< Accélération selon Y */
    float accel_z;      /*!< Accélération selon Z */
    float gyro_x;       /*!< Vitesse angulaire selon X */
    float gyro_y;       /*!< Vitesse angulaire selon Y */
    float gyro_z;       /*!< Vitesse angulaire selon Z */
    float temperature;  /*!< Température du capteur */
} SensorData;

/**
 * @brief Initialise les deux capteurs MPU6050
 * 
 * @return true si au moins un capteur a été initialisé avec succès, false sinon
 * @post Les capteurs sont prêts pour la lecture des données
 */
bool init_sensors(void);

/**
 * @brief Lit les données des deux capteurs
 * 
 * @return true si la lecture s'est bien déroulée, false sinon
 */
bool read_sensor_data(void);

/**
 * @brief Obtient les données du premier capteur MPU6050
 * 
 * @return Pointeur vers les données du MPU1
 */
const MPU6050_t* get_mpu1_data(void);

/**
 * @brief Calcule les angles à partir des accéléromètres et gyroscopes des capteurs
 * 
 * @post Les angles filtrés sont disponibles dans g_state
 */
void calculate_angles(void);

/**
 * @brief Obtient les données du second capteur MPU6050
 * 
 * @return Pointeur vers les données du MPU2
 */
const MPU6050_t* get_mpu2_data(void);

/**
 * @brief Met à jour les angles
 * 
 * @return true si la mise à jour s'est bien déroulée, false sinon
 */
bool update_sensor_angles(void);

#endif /* SENSORS_H_ */