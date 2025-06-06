/**
 *******************************************************************************
 * @file    sensors.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour la gestion des capteurs (MPU6050)
 *******************************************************************************
 */

#include "sensors.h"
#include "state.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_gpio.h"
#include "MPU6050/stm32g4_mpu6050.h"
#include <math.h>
#include "stm32g431xx.h" // Ajout explicite de l'include stm32g431xx.h

// Variables globales
static MPU6050_t MPU6050_Data1;  // Premier capteur (AD0 = 0)

SystemState g_state = {
    .angle_MPU1 = 0.0f,
    .command_position = 0.0f,
    .asservissement_value = 0.0f,
    .statut_moteur1 = 0,
    .statut_moteur2 = 0,
    .system_ok = true
};

// Implémentation des fonctions
bool init_sensors(void) {
    // --- Configuration GPIO pour alimentation et I2C ---
    // PA0 : alimentation du capteur (sortie, niveau haut)
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_NO_AF);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    // PB7 : SDA I2C, PA15 : SCL I2C (AF4, open-drain, pull-up)
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_HIGH, GPIO_AF4_I2C1);
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_15, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_HIGH, GPIO_AF4_I2C1);

    MPU6050_Result_t result1;
    bool status = true;
    
    printf("\r\n***** INITIALISATION DU CAPTEUR MPU6050 *****\r\n");
    
    // Initialisation du capteur MPU6050 (AD0 = 0)
    result1 = MPU6050_Init(&MPU6050_Data1, NULL, 0, MPU6050_Device_0, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    if (result1 == MPU6050_Result_Ok) {
        printf("MPU1 (AD0=0) : Initialisation réussie\r\n");
    } else {
        printf("MPU1 (AD0=0) : ERREUR d'initialisation (code %d)\r\n", result1);
        status = false;
    }
    
    // Test rapide du capteur si initialisation OK
    if (status) {
        printf("\r\n***** TEST DU CAPTEUR MPU6050 *****\r\n");
        if (MPU6050_ReadAll(&MPU6050_Data1) == MPU6050_Result_Ok) {
            printf("MPU1 Accéléromètre (g) : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data1.Accelerometer_X / MPU6050_ACCE_SENS_8,
                   MPU6050_Data1.Accelerometer_Y / MPU6050_ACCE_SENS_8,
                   MPU6050_Data1.Accelerometer_Z / MPU6050_ACCE_SENS_8);
            printf("MPU1 Gyroscope (°/s)   : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data1.Gyroscope_X / MPU6050_GYRO_SENS_500,
                   MPU6050_Data1.Gyroscope_Y / MPU6050_GYRO_SENS_500,
                   MPU6050_Data1.Gyroscope_Z / MPU6050_GYRO_SENS_500);
            printf("MPU1 Température       : %.1f°C\r\n", MPU6050_Data1.Temperature);
            if (MPU6050_Data1.Accelerometer_Z > 8000) {
                printf("MPU1: Accéléromètre Z OK (proche de 1g)\r\n");
            } else {
                printf("MPU1: Accéléromètre Z suspect (attendu ~1g)\r\n");
                printf("      Vérifiez la position du capteur ou la connexion\r\n");
            }
        } else {
            printf("MPU1: Erreur de lecture des données\r\n");
            status = false;
        }
        printf("\r\n");
    }
    
    return status;
}

bool read_sensor_data(void) {
    // Lecture des données du capteur MPU1 uniquement
    MPU6050_Result_t result1 = MPU6050_ReadAll(&MPU6050_Data1);
    return (result1 == MPU6050_Result_Ok);
}

const MPU6050_t* get_mpu1_data(void) {
    return &MPU6050_Data1;
}

bool update_sensor_angles(void) {
    if (!read_sensor_data()) {
        g_state.system_ok = false;
        return false;
    }
    g_state.system_ok = true;
    // Calcul de l'angle à partir du MPU1
    g_state.angle_MPU1 = atanf((float)MPU6050_Data1.Accelerometer_X / MPU6050_Data1.Accelerometer_Z) * 180.0f / M_PI;
    // Affichage des données brutes et de l'angle dans le terminal série
    printf("MPU1 Acc (g): X=%.2f Y=%.2f Z=%.2f | Gyro (°/s): X=%.2f Y=%.2f Z=%.2f | Angle=%.2f°\r\n",
        MPU6050_Data1.Accelerometer_X / MPU6050_ACCE_SENS_8,
        MPU6050_Data1.Accelerometer_Y / MPU6050_ACCE_SENS_8,
        MPU6050_Data1.Accelerometer_Z / MPU6050_ACCE_SENS_8,
        MPU6050_Data1.Gyroscope_X / MPU6050_GYRO_SENS_500,
        MPU6050_Data1.Gyroscope_Y / MPU6050_GYRO_SENS_500,
        MPU6050_Data1.Gyroscope_Z / MPU6050_GYRO_SENS_500,
        g_state.angle_MPU1);
    return true;
}
