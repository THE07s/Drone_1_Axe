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
#include "MPU6050/stm32g4_mpu6050.h"
#include <math.h>

// Variables globales
static MPU6050_t MPU6050_Data1;  // Premier capteur (AD0 = 0)
static MPU6050_t MPU6050_Data2;  // Second capteur (AD0 = 1)

// Implémentation des fonctions
bool init_sensors(void) {
    MPU6050_Result_t result1, result2;
    bool status = true;
    
    printf("\r\n***** INITIALISATION DES CAPTEURS MPU6050 *****\r\n");
    
    // Initialisation du premier capteur MPU6050 (AD0 = 0)
    // Dans le cas où le capteur est alimenté directement (pas via GPIO), on utilise NULL
    result1 = MPU6050_Init(&MPU6050_Data1, NULL, 0, MPU6050_Device_0, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    if (result1 == MPU6050_Result_Ok) {
        printf("MPU1 (AD0=0) : Initialisation réussie\r\n");
    } else {
        printf("MPU1 (AD0=0) : ERREUR d'initialisation (code %d)\r\n", result1);
        status = false;
    }
    
    // Initialisation du second capteur MPU6050 (AD0 = 1)
    // Dans le cas où le capteur est alimenté directement (pas via GPIO), on utilise NULL
    result2 = MPU6050_Init(&MPU6050_Data2, NULL, 0, MPU6050_Device_1, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    if (result2 == MPU6050_Result_Ok) {
        printf("MPU2 (AD0=1) : Initialisation réussie\r\n");
    } else {
        printf("MPU2 (AD0=1) : ERREUR d'initialisation (code %d)\r\n", result2);
        status = false;
    }
    
    // Si les deux capteurs sont correctement initialisés, effectuer des tests rapides
    if (status) {
        printf("\r\n***** TEST DES CAPTEURS MPU6050 *****\r\n");
        
        // Première lecture du MPU1
        if (MPU6050_ReadAll(&MPU6050_Data1) == MPU6050_Result_Ok) {
            // Afficher toutes les données du capteur MPU1 directement dans le terminal
            printf("MPU1 Accéléromètre (g) : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data1.Accelerometer_X / MPU6050_ACCE_SENS_8,
                   MPU6050_Data1.Accelerometer_Y / MPU6050_ACCE_SENS_8,
                   MPU6050_Data1.Accelerometer_Z / MPU6050_ACCE_SENS_8);
            
            printf("MPU1 Gyroscope (°/s)   : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data1.Gyroscope_X / MPU6050_GYRO_SENS_500,
                   MPU6050_Data1.Gyroscope_Y / MPU6050_GYRO_SENS_500,
                   MPU6050_Data1.Gyroscope_Z / MPU6050_GYRO_SENS_500);
            
            printf("MPU1 Température       : %.1f°C\r\n", MPU6050_Data1.Temperature);
            
            // Validation de l'accéléromètre Z (doit être proche de 1g en position normale)
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
        
        // Première lecture du MPU2
        if (MPU6050_ReadAll(&MPU6050_Data2) == MPU6050_Result_Ok) {
            // Afficher toutes les données du capteur MPU2 directement dans le terminal
            printf("MPU2 Accéléromètre (g) : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data2.Accelerometer_X / MPU6050_ACCE_SENS_8,
                   MPU6050_Data2.Accelerometer_Y / MPU6050_ACCE_SENS_8,
                   MPU6050_Data2.Accelerometer_Z / MPU6050_ACCE_SENS_8);
            
            printf("MPU2 Gyroscope (°/s)   : X=%.2f | Y=%.2f | Z=%.2f\r\n", 
                   MPU6050_Data2.Gyroscope_X / MPU6050_GYRO_SENS_500,
                   MPU6050_Data2.Gyroscope_Y / MPU6050_GYRO_SENS_500,
                   MPU6050_Data2.Gyroscope_Z / MPU6050_GYRO_SENS_500);
            
            printf("MPU2 Température       : %.1f°C\r\n", MPU6050_Data2.Temperature);
            
            // Validation de l'accéléromètre Z (doit être proche de 1g en position normale)
            if (MPU6050_Data2.Accelerometer_Z > 8000) {
                printf("MPU2: Accéléromètre Z OK (proche de 1g)\r\n");
            } else {
                printf("MPU2: Accéléromètre Z suspect (attendu ~1g)\r\n");
                printf("      Vérifiez la position du capteur ou la connexion\r\n");
            }
        } else {
            printf("MPU2: Erreur de lecture des données\r\n");
            status = false;
        }
        
        // Pause pour permettre de voir les résultats de test
        printf("\r\nAttente de 2 secondes pour visualisation des données...\r\n");
        HAL_Delay(2000);
    }
    
    return status;
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

bool update_sensor_angles(void) {
    if (!read_sensor_data()) {
        system_ok = false;
        return false;
    }

    system_ok = true;

    angle_MPU1 = atanf((float)MPU6050_Data1.Accelerometer_X / MPU6050_Data1.Accelerometer_Z) * 180.0f / M_PI;
    angle_MPU2 = atanf((float)MPU6050_Data2.Accelerometer_X / MPU6050_Data2.Accelerometer_Z) * 180.0f / M_PI;

    return true;
}
