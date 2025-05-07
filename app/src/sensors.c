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
    bool status = true;
    char buffer[50];
    
    printf("Test d'initialisation des capteurs MPU6050...\r\n");
    
    // Initialisation du premier capteur MPU6050 (AD0 = 0)
    result1 = MPU6050_Init(&MPU6050_Data1, GPIOA, GPIO_PIN_0, MPU6050_Device_0, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    if (result1 == MPU6050_Result_Ok) {
        printf("MPU1 (AD0=0) : Initialisation réussie\r\n");
    } else {
        printf("MPU1 (AD0=0) : ERREUR d'initialisation (code %d)\r\n", result1);
        status = false;
    }
    
    // Initialisation du second capteur MPU6050 (AD0 = 1)
    result2 = MPU6050_Init(&MPU6050_Data2, GPIOA, GPIO_PIN_0, MPU6050_Device_1, 
                          MPU6050_Accelerometer_8G, MPU6050_Gyroscope_500s);
    
    if (result2 == MPU6050_Result_Ok) {
        printf("MPU2 (AD0=1) : Initialisation réussie\r\n");
    } else {
        printf("MPU2 (AD0=1) : ERREUR d'initialisation (code %d)\r\n", result2);
        status = false;
    }
    
    // Si les deux capteurs sont correctement initialisés, effectuer des tests rapides
    if (status) {
        printf("Test de lecture des capteurs...\r\n");
        
        // Première lecture du MPU1
        if (MPU6050_ReadAll(&MPU6050_Data1) == MPU6050_Result_Ok) {
            // Vérifier que les données sont cohérentes (non nulles et dans des plages attendues)
            if (MPU6050_Data1.Accelerometer_Z > 8000) {  // ~ 1g en position normale
                sprintf(buffer, "MPU1: Accéléromètre Z OK (%.2f g)", 
                        MPU6050_Data1.Accelerometer_Z / MPU6050_ACCE_SENS_8);
                printf("%s\r\n", buffer);
            } else {
                sprintf(buffer, "MPU1: Accéléromètre Z suspect (%.2f g)", 
                        MPU6050_Data1.Accelerometer_Z / MPU6050_ACCE_SENS_8);
                printf("%s\r\n", buffer);
            }
            
            // Température pour vérifier que le capteur est actif
            sprintf(buffer, "MPU1: Température = %.1f°C", MPU6050_Data1.Temperature);
            printf("%s\r\n", buffer);
        } else {
            printf("MPU1: Erreur de lecture des données\r\n");
            status = false;
        }
        
        // Première lecture du MPU2
        if (MPU6050_ReadAll(&MPU6050_Data2) == MPU6050_Result_Ok) {
            // Vérifier que les données sont cohérentes (non nulles et dans des plages attendues)
            if (MPU6050_Data2.Accelerometer_Z > 8000) {  // ~ 1g en position normale
                sprintf(buffer, "MPU2: Accéléromètre Z OK (%.2f g)", 
                        MPU6050_Data2.Accelerometer_Z / MPU6050_ACCE_SENS_8);
                printf("%s\r\n", buffer);
            } else {
                sprintf(buffer, "MPU2: Accéléromètre Z suspect (%.2f g)", 
                        MPU6050_Data2.Accelerometer_Z / MPU6050_ACCE_SENS_8);
                printf("%s\r\n", buffer);
            }
            
            // Température pour vérifier que le capteur est actif
            sprintf(buffer, "MPU2: Température = %.1f°C", MPU6050_Data2.Temperature);
            printf("%s\r\n", buffer);
        } else {
            printf("MPU2: Erreur de lecture des données\r\n");
            status = false;
        }
        
        // Pause pour permettre de voir les résultats de test
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