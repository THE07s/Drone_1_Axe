/**
 * @file sensors.c
 * @brief Implémentation du module de gestion des capteurs MPU6050
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#include "sensors.h"
#include <stdio.h>
#include <math.h>
#include "stm32g4xx_hal.h"
#include "../config.h"

// Variables globales
static MPU6050_t MPU6050_Data1;  /*!< Premier capteur (AD0 = 0) */
static MPU6050_t MPU6050_Data2;  /*!< Deuxième capteur (AD0 = 1) */

bool MPU1_ok = false;  /*!< État d'init du 1er capteur */
bool MPU2_ok = false;  /*!< État d'init du 2nd capteur */

/**
 * @brief Structure d'état global du système
 */
SystemState g_state = {
    .angle_MPU1 = 0.0f,
    .command_position = 0.0f,
    .asservissement_value = 0.0f,
    .statut_moteur1 = 0,
    .statut_moteur2 = 0,
    .system_ok = true
};


static float Q_angle1 = 0.001f; /*!< Variance du bruit de l'angle pour le MPU1. */
static float Q_bias1  = 0.003f; /*!< Variance du bruit du biais pour le MPU1. */
static float R_measure1 = 0.03f; /*!< Variance du bruit de mesure pour le MPU1. */
static float angle1 = 0.0f; /*!< Angle estimé pour le MPU1. */
static float bias1  = 0.0f; /*!< Biais estimé pour le MPU1. */
static float P1[2][2] = {{0, 0}, {0, 0}}; /*!< Matrice de covariance du filtre de Kalman pour le MPU1. */

// Paramètres Kalman pour MPU2
static float Q_angle2 = 0.001f; /*!< Variance du bruit de l'angle pour le MPU2. */
static float Q_bias2  = 0.003f; /*!< Variance du bruit du biais pour le MPU2. */
static float R_measure2 = 0.03f; /*!< Variance du bruit de mesure pour le MPU2. */
static float angle2 = 0.0f; /*!< Angle estimé pour le MPU2. */
static float bias2  = 0.0f; /*!< Biais estimé pour le MPU2. */
static float P2[2][2] = {{0, 0}, {0, 0}}; /*!< Matrice de covariance du filtre de Kalman pour le MPU2. */

bool init_sensors(void) {
    // Initialisation du premier capteur (AD0 = 0)
    if (MPU6050_Init(&MPU6050_Data1, GPIOA, GPIO_PIN_0, MPU6050_Device_0, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_500s) == MPU6050_Result_Ok) {
        MPU1_ok = true;
    }

        // Initialisation du deuxième capteur (AD0 = 1)
    if (MPU6050_Init(&MPU6050_Data2, GPIOA, GPIO_PIN_0, MPU6050_Device_1, MPU6050_Accelerometer_4G, MPU6050_Gyroscope_500s) == MPU6050_Result_Ok) {
        MPU2_ok = true;
    }

#if DEBUG_SENSORS
    // Affichage dans le terminal pour le debug
    while (1)
    {
        if (MPU1_ok) MPU6050_ReadAll(&MPU6050_Data1);
        if (MPU2_ok) MPU6050_ReadAll(&MPU6050_Data2);
        display_raw_data();  // Affichage des données brutes
        calculate_angles();  // Calcul des angles à partir des données brutes
        printf("MPU1 Angle: %.2f, MPU2 Angle: %.2f\n", g_state.angle_MPU1, g_state.command_position);
        HAL_Delay(1000);  // Attendre 1 seconde avant la prochaine lecture
    }
#endif

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

void update_MPU_data_angles() {
    MPU6050_ReadAll(&MPU6050_Data1);
    MPU6050_ReadAll(&MPU6050_Data2);
}

// Fonction de mise à jour Kalman générique
static float Kalman_Update(float* angle, float* bias, float P[2][2], float Q_angle, float Q_bias, float R_measure, float newAngle, float newRate, float dt) {
    // Prédiction
    newRate -= *bias;
    *angle += dt * newRate;
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;
    // Mesure
    float S = P[0][0] + R_measure;
    float K0 = P[0][0] / S;
    float K1 = P[1][0] / S;
    float y = newAngle - *angle;
    *angle += K0 * y;
    *bias  += K1 * y;
    // Mise à jour de P
    float P00 = P[0][0], P01 = P[0][1];
    P[0][0] -= K0 * P00;
    P[0][1] -= K0 * P01;
    P[1][0] -= K1 * P00;
    P[1][1] -= K1 * P01;
    return *angle;
}
void calculate_angles(void) {
    static uint32_t prev_tick = 0;
    uint32_t current_tick = HAL_GetTick();
    float dt = (current_tick - prev_tick) / 1000.0f;
    prev_tick = current_tick;

    // Lecture des données des capteurs
    update_MPU_data_angles();

#if DEBUG_SENSORS
    display_raw_data();
#endif

    // Mise à jour Kalman pour le pitch
    float accX1 = -MPU6050_Data1.Accelerometer_X / 8192.0f;
    float accY1 = MPU6050_Data1.Accelerometer_Y / 8192.0f;
    float accZ1 = MPU6050_Data1.Accelerometer_Z / 8192.0f;
    float gyrY1 = -MPU6050_Data1.Gyroscope_Y / 65.5f;

    float accX2 = MPU6050_Data2.Accelerometer_X / 8192.0f;
    float accY2 = MPU6050_Data2.Accelerometer_Y / 8192.0f;
    float accZ2 = MPU6050_Data2.Accelerometer_Z / 8192.0f;
    float gyrY2 = MPU6050_Data2.Gyroscope_Y / 65.5f;

    float pitch_kalman1 = Kalman_Update(&angle1, &bias1, P1, Q_angle1, Q_bias1, R_measure1,
        atan2f(-accX1, sqrtf(accY1 * accY1 + accZ1 * accZ1)) * 180.0f / M_PI,
        gyrY1, dt);
    float pitch_kalman2 = Kalman_Update(&angle2, &bias2, P2, Q_angle2, Q_bias2, R_measure2,
        atan2f(-accX2, sqrtf(accY2 * accY2 + accZ2 * accZ2)) * 180.0f / M_PI,
        gyrY2, dt);

    // Saturation à [-90°, 90°]
    if (pitch_kalman1 > 90.0f)  pitch_kalman1 = 90.0f;
    if (pitch_kalman1 < -90.0f) pitch_kalman1 = -90.0f;
    if (pitch_kalman2 > 90.0f)  pitch_kalman2 = 90.0f;
    if (pitch_kalman2 < -90.0f) pitch_kalman2 = -90.0f;

    g_state.angle_MPU1      = pitch_kalman1;
    g_state.command_position = pitch_kalman2;

    // [DEBUG]
    // printf("Kalman Filter : Pitch MPU1 = %.2f°, MPU2 = %.2f°\n", pitch_kalman1, pitch_kalman2);
}