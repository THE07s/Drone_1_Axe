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
extern int g_constante;

void test_display(void) {
    // Titre du projet
    ILI9341_Puts(40, 20, "DRONE 1 AXE", &Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
    ILI9341_Puts(40, 40, "Test Ecran", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

    // Rectangle
    ILI9341_DrawRectangle(40, 70, 120, 120, ILI9341_COLOR_RED);

    // Cercle
    ILI9341_DrawFilledCircle(180, 95, 25, ILI9341_COLOR_BLUE);

    // Lignes
    ILI9341_DrawLine(40, 150, 280, 150, ILI9341_COLOR_GREEN);
    ILI9341_DrawLine(160, 130, 160, 170, ILI9341_COLOR_GREEN);

    // Texte
    ILI9341_Puts(40, 180, "Test des couleurs:", &Font_7x10, ILI9341_COLOR_CYAN, ILI9341_COLOR_BLACK);
    ILI9341_Puts(40, 195, "ROUGE", &Font_7x10, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    ILI9341_Puts(100, 195, "VERT", &Font_7x10, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
    ILI9341_Puts(160, 195, "BLEU", &Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_BLACK);
    ILI9341_Puts(220, 195, "JAUNE", &Font_7x10, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);

    HAL_Delay(3000);

    ILI9341_Fill(ILI9341_COLOR_BLACK);
}

// Implémentation des fonctions
void init_display(void) {
    ILI9341_Init();
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    ILI9341_Fill(ILI9341_COLOR_BLACK);
    test_display();
}

void display_angle(float angle, int x, int y) {
    sprintf(display_buffer, "Angle: %.2f deg", angle);
    ILI9341_Puts(x, y, display_buffer, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void display_inclination_line(int x1, int y1, int x2, int y2, uint16_t color) {
    ILI9341_DrawLine(x1, y1, x2, y2, color);
}

void clear_display(void) {
    ILI9341_Fill(ILI9341_COLOR_BLACK);
}

void display_monitoring_info(float angle, float command_position, float mpu1_angle, float mpu2_angle, int motor1_status, int motor2_status, int control_status) {
    // Effacer l'écran
    ILI9341_Fill(ILI9341_COLOR_BLACK);

    // --- Représentation visuelle du système (perspective, 17 arêtes) ---
    // Socle (rectangle en perspective)
    ILI9341_DrawLine(60, 210, 180, 210, ILI9341_COLOR_GRAY);    // face avant
    ILI9341_DrawLine(60, 210, 70, 230, ILI9341_COLOR_GRAY);     // côté gauche
    ILI9341_DrawLine(180, 210, 190, 230, ILI9341_COLOR_GRAY);   // côté droit
    ILI9341_DrawLine(70, 230, 190, 230, ILI9341_COLOR_GRAY);    // face arrière
    ILI9341_DrawLine(60, 210, 60, 200, ILI9341_COLOR_GRAY);     // coin avant gauche
    ILI9341_DrawLine(180, 210, 180, 200, ILI9341_COLOR_GRAY);   // coin avant droit
    ILI9341_DrawLine(70, 230, 70, 220, ILI9341_COLOR_GRAY);     // coin arrière gauche
    ILI9341_DrawLine(190, 230, 190, 220, ILI9341_COLOR_GRAY);   // coin arrière droit
    ILI9341_DrawLine(60, 200, 180, 200, ILI9341_COLOR_GRAY);    // face avant haut
    ILI9341_DrawLine(70, 220, 190, 220, ILI9341_COLOR_GRAY);    // face arrière haut
    ILI9341_DrawLine(60, 200, 70, 220, ILI9341_COLOR_GRAY);     // côté gauche haut
    ILI9341_DrawLine(180, 200, 190, 220, ILI9341_COLOR_GRAY);   // côté droit haut

    // Tige verticale (rectangle)
    ILI9341_DrawLine(120, 200, 120, 120, ILI9341_COLOR_WHITE);  // côté gauche
    ILI9341_DrawLine(130, 200, 130, 120, ILI9341_COLOR_WHITE);  // côté droit
    ILI9341_DrawLine(120, 120, 130, 120, ILI9341_COLOR_WHITE);  // haut
    ILI9341_DrawLine(120, 200, 130, 200, ILI9341_COLOR_WHITE);  // bas

    // Tige horizontale (qui bouge, rotation selon angle)
    int x_center = 125;
    int y_center = 120;
    int demi_longueur = 60;
    float rad = angle * M_PI / 180.0f;
    int x1 = x_center - (int)(demi_longueur * cos(rad));
    int y1 = y_center - (int)(demi_longueur * sin(rad));
    int x2 = x_center + (int)(demi_longueur * cos(rad));
    int y2 = y_center + (int)(demi_longueur * sin(rad));
    ILI9341_DrawLine(x1, y1, x2, y2, ILI9341_COLOR_YELLOW); // tige horizontale
    // extrémités de la tige horizontale
    ILI9341_DrawFilledCircle(x1, y1, 4, ILI9341_COLOR_BLUE); // MPU1
    ILI9341_DrawFilledCircle(x2, y2, 4, ILI9341_COLOR_BLUE); // MPU2

    // Affichage de l'angle au centre
    sprintf(display_buffer, "%.2f°", angle);
    ILI9341_Puts(x_center - 20, y_center - 25, display_buffer, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

    // Affichage de la position de commande en bas
    sprintf(display_buffer, "Position de commande: %.2f°", command_position);
    ILI9341_Puts(10, 300, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

    // Affichage du statut système à droite
    int x_stat = 180;
    int y_stat = 10;
    ILI9341_Puts(x_stat, y_stat, "Statut systeme:", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    sprintf(display_buffer, "Moteur 1: %s", motor1_status ? "ON" : "OFF");
    ILI9341_Puts(x_stat, y_stat + 20, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    sprintf(display_buffer, "Moteur 2: %s", motor2_status ? "ON" : "OFF");
    ILI9341_Puts(x_stat, y_stat + 35, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    sprintf(display_buffer, "MPU1: %.2f°", mpu1_angle);
    ILI9341_Puts(x_stat, y_stat + 50, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    sprintf(display_buffer, "MPU2: %.2f°", mpu2_angle);
    ILI9341_Puts(x_stat, y_stat + 65, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
    sprintf(display_buffer, "Asservissement: %s", control_status ? "ON" : "OFF");
    ILI9341_Puts(x_stat, y_stat + 80, display_buffer, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

