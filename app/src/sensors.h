#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdbool.h>
#include <stdint.h>
#include "MPU6050/stm32g4_mpu6050.h"
#include "state.h"

// Structure pour stocker les données des capteurs
typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float temperature;
} SensorData;

// Initialisation des deux capteurs MPU6050
bool init_sensors(void);

// Lecture des données des deux capteurs
bool read_sensor_data(void);

// Obtenir les données du premier capteur MPU6050
const MPU6050_t* get_mpu1_data(void);

void calculate_angles(void);

// Obtenir les données du second capteur MPU6050
const MPU6050_t* get_mpu2_data(void);

// Mettre à jour les angles globaux depuis les capteurs
bool update_sensor_angles(void);

#endif /* SENSORS_H_ */