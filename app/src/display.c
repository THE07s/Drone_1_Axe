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
#include <stdio.h>
#include <string.h>
#include <math.h>

// Variables globales
char display_buffer[32];
extern int constante;  // Déclaration de variable externe définie dans main.c

// Implémentation des fonctions
void init_display(void) {
    // Code d'initialisation de l'écran ILI9341
    ILI9341_Init();
    ILI9341_SetRotation(ILI9341_Orientation_Landscape_1);  // Rotation pour orientation paysage
    ILI9341_Fill(ILI9341_COLOR_BLACK);  // Fond noir
}

<<<<<<< HEAD
void display_angle(int x,int y) {
	int y1 = 240 - constante;
	float resultat = atan((120.0 - constante) / 160.0);  // Calcul angle d'inclinaison à partir de la constante
	float resultat_deg = resultat * (180.0 / M_PI);  // Conversion en degrés
	sprintf(str, "angle = %.2f", resultat_deg); // %.2f affiche avec 2 d�cimales

}

void display_inclination_line(int x1, int y1, int x2, int y2) {
	ILI9341_DrawLine(0,y1,320,constante,ILI9341_COLOR_RED);
=======
void display_angle(float angle, int x, int y) {
    // Affichage de l'angle avec formatage
    sprintf(display_buffer, "Angle: %.2f deg", angle);
    ILI9341_WriteString(x, y, display_buffer, Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void display_inclination_line(int x1, int y1, int x2, int y2, uint16_t color) {
    // Affichage d'une ligne d'inclinaison
    ILI9341_DrawLine(x1, y1, x2, y2, color);
>>>>>>> 288e2ff70acd13d9846af6e068aa0bbf51b3429c
}

void clear_display(void) {
    // Effacement complet de l'écran
    ILI9341_Fill(ILI9341_COLOR_BLACK);
}

// Autres fonctions selon les besoins
