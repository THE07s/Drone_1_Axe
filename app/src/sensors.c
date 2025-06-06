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
#include <stdint.h>
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal.h"
#include "MPU6050/stm32g4_mpu6050.h"
#include <math.h>
#include "stm32g431xx.h"

// Variables globales
static MPU6050_t MPU6050_Data1;  // Premier capteur (AD0 = 0)
static MPU6050_t MPU6050_Data2;  // Deuxième capteur (AD0 = 1)

bool MPU1_ok = false;
bool MPU2_ok = false;

SystemState g_state = {
    .angle_MPU1 = 0.0f,
    .command_position = 0.0f,
    .asservissement_value = 0.0f,
    .statut_moteur1 = 0,
    .statut_moteur2 = 0,
    .system_ok = true
};

bool init_sensors(void) {
    // Initialisation du premier capteur (AD0 = 0)
    if (MPU6050_Init(&MPU6050_Data1, GPIOA, GPIO_PIN_0, MPU6050_Device_0, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_2000s) == MPU6050_Result_Ok) {
        MPU1_ok = true;
    }
    // Initialisation du deuxième capteur (AD0 = 1)
    if (MPU6050_Init(&MPU6050_Data2, GPIOA, GPIO_PIN_0, MPU6050_Device_1, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_2000s) == MPU6050_Result_Ok) {
        MPU2_ok = true;
    }

    // Affichage dans le terminal pour le debug
    while (1)
    {
        if (MPU1_ok) MPU6050_ReadAll(&MPU6050_Data1);
        if (MPU2_ok) MPU6050_ReadAll(&MPU6050_Data2);
        display_raw_data();  // Affichage des données brutes
        calculate_angles();  // Calcul des angles à partir des données brutes
        printf("MPU1 Angle: %.2f, MPU2 Angle: %.2f\n", g_state.angle_MPU1, g_state.angle_MPU2);
        HAL_Delay(1000);  // Attendre 1 seconde avant la prochaine lecture
    }
    return MPU1_ok || MPU2_ok;
}

void display_raw_data(void) {
    // Affichage des données brutes des capteurs
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMPU1: AccX=%d AccY=%d AccZ=%d \n\ngyroX=%d gyroY=%d gyroZ=%d \n\nTemp=%.2f\n",
           MPU6050_Data1.Accelerometer_X, MPU6050_Data1.Accelerometer_Y, MPU6050_Data1.Accelerometer_Z,
           MPU6050_Data1.Gyroscope_X, MPU6050_Data1.Gyroscope_Y, MPU6050_Data1.Gyroscope_Z,
           MPU6050_Data1.Temperature);

    printf("MPU2: AccX=%d AccY=%d AccZ=%d \n\ngyroX=%d gyroY=%d gyroZ=%d \n\nTemp=%.2f\n",
           MPU6050_Data2.Accelerometer_X, MPU6050_Data2.Accelerometer_Y, MPU6050_Data2.Accelerometer_Z,
           MPU6050_Data2.Gyroscope_X, MPU6050_Data2.Gyroscope_Y, MPU6050_Data2.Gyroscope_Z,
           MPU6050_Data2.Temperature);
}

void calculate_angles(void) {
    if (MPU1_ok) MPU6050_ReadAll(&MPU6050_Data1);
    if (MPU2_ok) MPU6050_ReadAll(&MPU6050_Data2);

    // Calcul et affichage des angles autour de chaque axe (en français)
    // MPU1
    float ax1 = (float)MPU6050_Data1.Accelerometer_X;
    float ay1 = (float)MPU6050_Data1.Accelerometer_Y;
    float az1 = (float)MPU6050_Data1.Accelerometer_Z;
    float angle_autour_X1 = atan2f(-ax1, sqrtf(ay1 * ay1 + az1 * az1)) * 180.0f / M_PI;
    // float angle_autour_Y1 = atan2f(ay1, az1) * 180.0f / M_PI;

    // MPU2
    float ax2 = (float)MPU6050_Data2.Accelerometer_X;
    float ay2 = (float)MPU6050_Data2.Accelerometer_Y;
    float az2 = (float)MPU6050_Data2.Accelerometer_Z;
    float angle_autour_X2 = atan2f(-ax2, sqrtf(ay2 * ay2 + az2 * az2)) * 180.0f / M_PI;
    // float angle_autour_Y2 = atan2f(ay2, az2) * 180.0f / M_PI;

    // On stocke l'angle
    g_state.angle_MPU1 = angle_autour_X1;
    g_state.angle_MPU2 = angle_autour_X2;

    printf("MPU1 : Angle autour de l'axe X = %.2f°\n", angle_autour_X1);
    printf("MPU2 : Angle autour de l'axe X = %.2f°\n", angle_autour_X2);
}