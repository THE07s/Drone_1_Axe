/**
 *******************************************************************************
 * @file    display.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour la gestion de l'affichage
 *******************************************************************************
 */

#include "display.h"
#include "../config.h"
#include "../drivers/bsp/tft_ili9341/stm32g4_ili9341.h"
#include "sensors.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// Variables globales
char display_buffer[32];
extern int g_constante;  // au lieu de extern int constante;

// Implémentation des fonctions
void init_display(void) {
    // Code d'initialisation de l'écran ILI9341
    ILI9341_Init();
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    ILI9341_Fill(ILI9341_COLOR_BLACK);  // Fond noir
    
    // Tests de l'écran pour vérifier son bon fonctionnement
    
    // Affichage du titre du projet
    ILI9341_Puts(40, 20, "DRONE 1 AXE", &Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
    ILI9341_Puts(40, 40, "Test Ecran", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    
    // Test des formes géométriques
    // Dessiner un rectangle
    ILI9341_DrawRectangle(40, 70, 120, 120, ILI9341_COLOR_RED);
    
    // Dessiner un cercle
    ILI9341_DrawFilledCircle(180, 95, 25, ILI9341_COLOR_BLUE);
    
    // Dessiner des lignes d'inclinaison de test
    ILI9341_DrawLine(40, 150, 280, 150, ILI9341_COLOR_GREEN);
    ILI9341_DrawLine(160, 130, 160, 170, ILI9341_COLOR_GREEN);
    
    // Test d'affichage de texte avec différentes couleurs et polices
    ILI9341_Puts(40, 180, "Test des couleurs:", &Font_7x10, ILI9341_COLOR_CYAN, ILI9341_COLOR_BLACK);
    ILI9341_Puts(40, 195, "ROUGE", &Font_7x10, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    ILI9341_Puts(100, 195, "VERT", &Font_7x10, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
    ILI9341_Puts(160, 195, "BLEU", &Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_BLACK);
    ILI9341_Puts(220, 195, "JAUNE", &Font_7x10, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
    
    // Pause pour permettre de voir les tests
    HAL_Delay(3000);
    
    // Effacer l'écran pour préparer à l'affichage normal
    ILI9341_Fill(ILI9341_COLOR_BLACK);
}

void display_angle(float angle, int x, int y) {
    // Affichage de l'angle avec formatage
    sprintf(display_buffer, "Angle: %.2f deg", angle);
    ILI9341_Puts(x, y, display_buffer, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void display_inclination_line(int x1, int y1, int x2, int y2, uint16_t color) {
    // Affichage d'une ligne d'inclinaison
    ILI9341_DrawLine(x1, y1, x2, y2, color);
}

void clear_display(void) {
    // Effacement complet de l'écran
    ILI9341_Fill(ILI9341_COLOR_BLACK);
}

void display_sensor_data(void) {
    const MPU6050_t* MPU6050_Data1 = get_mpu1_data();
    const MPU6050_t* MPU6050_Data2 = get_mpu2_data();
    
    // Affichage des données dans le terminal
    printf("\r\n==== DONNÉES DES CAPTEURS MPU6050 ====\r\n\n");
    
    // Affichage des données du premier capteur (MPU1)
    printf("--- MPU1 ---\r\n");
    
    // Accélération X, Y, Z
    printf("Acc X: %.2f g  |  ", MPU6050_Data1->Accelerometer_X / MPU6050_ACCE_SENS_8);
    printf("Acc Y: %.2f g  |  ", MPU6050_Data1->Accelerometer_Y / MPU6050_ACCE_SENS_8);
    printf("Acc Z: %.2f g\r\n", MPU6050_Data1->Accelerometer_Z / MPU6050_ACCE_SENS_8);
    
    // Gyroscope X, Y, Z
    printf("Gyro X: %.2f °/s  |  ", MPU6050_Data1->Gyroscope_X / MPU6050_GYRO_SENS_500);
    printf("Gyro Y: %.2f °/s  |  ", MPU6050_Data1->Gyroscope_Y / MPU6050_GYRO_SENS_500);
    printf("Gyro Z: %.2f °/s\r\n", MPU6050_Data1->Gyroscope_Z / MPU6050_GYRO_SENS_500);
    
    // Température
    printf("Température: %.1f°C\r\n\n", MPU6050_Data1->Temperature);
    
    // Affichage des données du second capteur (MPU2)
    printf("--- MPU2 ---\r\n");
    
    // Accélération X, Y, Z
    printf("Acc X: %.2f g  |  ", MPU6050_Data2->Accelerometer_X / MPU6050_ACCE_SENS_8);
    printf("Acc Y: %.2f g  |  ", MPU6050_Data2->Accelerometer_Y / MPU6050_ACCE_SENS_8);
    printf("Acc Z: %.2f g\r\n", MPU6050_Data2->Accelerometer_Z / MPU6050_ACCE_SENS_8);
    
    // Gyroscope X, Y, Z
    printf("Gyro X: %.2f °/s  |  ", MPU6050_Data2->Gyroscope_X / MPU6050_GYRO_SENS_500);
    printf("Gyro Y: %.2f °/s  |  ", MPU6050_Data2->Gyroscope_Y / MPU6050_GYRO_SENS_500);
    printf("Gyro Z: %.2f °/s\r\n", MPU6050_Data2->Gyroscope_Z / MPU6050_GYRO_SENS_500);
    
    // Température
    printf("Température: %.1f°C\r\n", MPU6050_Data2->Temperature);
    
    printf("\r\n===================================\r\n");
}

// Autres fonctions selon les besoins
