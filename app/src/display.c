/**
 *******************************************************************************
 * @file    display.c
 * @author  Drone_1_Axe Team
 * @date    Avril 23, 2025
 * @brief   Implémentation de l'interface pour la gestion de l'affichage
 *******************************************************************************
 */

#include "display.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include <stdio.h>
#include <string.h>
#include "main.c"

// Variables globales
char display_buffer[32];

// Implémentation des fonctions
void init_display(void) {
    // Code d'initialisation de l'écran à compléter
}

void display_angle(float angle,int x,int y) {
	int y1 = 240 - constante;
	float resultat = atan((120.0 - constante) / 160.0);  // Calcul angle d'inclinaison à partir de la constante
	float resultat_deg = resultat * (180.0 / M_PI);  // Conversion en degrés
	sprintf(str, "angle = %.2f", resultat_deg); // %.2f affiche avec 2 d�cimales

}

void display_inclination_line(int x1, int y1, int x2, int y2, char color) {
	ILI9341_DrawLine(0,y1,320,constante,color);
}

void clear_display(void) {
    // Code d'effacement de l'écran à compléter
}

// Autres fonctions selon les besoins
