/**
 *******************************************************************************
 * @file    display.h
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Interface pour la gestion de l'affichage sur l'écran ILI9341
 *******************************************************************************
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>  // Pour uint16_t

 /* Définitions des couleurs (reprises depuis stm32g4_ili9341.h) */
#define DISPLAY_COLOR_BLACK       0x0000
#define DISPLAY_COLOR_BLUE        0x001F
#define DISPLAY_COLOR_RED         0xF800
#define DISPLAY_COLOR_GREEN       0x07E0
#define DISPLAY_COLOR_CYAN        0x07FF
#define DISPLAY_COLOR_MAGENTA     0xF81F
#define DISPLAY_COLOR_YELLOW      0xFFE0
#define DISPLAY_COLOR_WHITE       0xFFFF

// Initialisation de l'écran
void init_display(void);

// Fonction de test de l'affichage
void test_display(void);

// Affichage de l'angle d'inclinaison
void display_angle(float angle, int x, int y);

// Affichage de la ligne d'inclinaison
void display_inclination_line(int x1, int y1, int x2, int y2, uint16_t color);

// Effacement de l'écran ou d'une zone
void clear_display(void);

// Affichage des données des capteurs MPU6050
void display_monitoring_info(float angle, float command_position, float mpu1_angle, float mpu2_angle, int motor1_status, int motor2_status, int control_status);

// Autres fonctions selon les besoins

#endif /* DISPLAY_H_ */
