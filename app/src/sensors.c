/**
 *******************************************************************************
 * @file    sensors.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour la gestion des capteurs (MPU6050)
 *******************************************************************************
 */

#include "sensors.h"
#include <stdio.h>

// Variables globales
static MPU6050_t MPU6050_Data1;  // Premier capteur (AD0 = 0)
static MPU6050_t MPU6050_Data2;  // Second capteur (AD0 = 1)

// Implémentation des fonctions
bool init_sensors(void) {
    MPU6050_Result_t result1, result2;
    
    // Initialisation du premier capteur MPU6050 (AD0 = 0)
    result1 = MPU6050_Init(&MPU6050_Data1, GPIOA, GPIO_PIN_0, MPU6050_Device_0, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    // Initialisation du second capteur MPU6050 (AD0 = 1)
    result2 = MPU6050_Init(&MPU6050_Data2, GPIOA, GPIO_PIN_0, MPU6050_Device_1, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    return (result1 == MPU6050_Result_Ok && result2 == MPU6050_Result_Ok);
}

bool read_sensor_data(void) {
    MPU6050_Result_t result1, result2;
    
    // Lecture des données du premier capteur
    result1 = MPU6050_ReadAll(&MPU6050_Data1);
    
    // Lecture des données du second capteur
    result2 = MPU6050_ReadAll(&MPU6050_Data2);
    
    return (result1 == MPU6050_Result_Ok && result2 == MPU6050_Result_Ok);
}

const MPU6050_t* get_mpu1_data(void) {
    return &MPU6050_Data1;
}

const MPU6050_t* get_mpu2_data(void) {
    return &MPU6050_Data2;
}