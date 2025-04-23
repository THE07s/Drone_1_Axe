/**
 *******************************************************************************
 * @file    sensors.h
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Interface pour la gestion des capteurs (MPU6050)
 *******************************************************************************
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdbool.h>
#include "MPU6050/stm32g4_mpu6050.h"

// Structure pour stocker les données des capteurs
typedef struct {
    // À compléter selon les besoins
} SensorData;

// Initialisation du capteur MPU6050
bool init_sensors(void);

// Lecture des données du capteur
bool read_sensor_data(void);

// Autres fonctions selon les besoins

#endif /* SENSORS_H_ */