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
#include "state.h"
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

#define NOIR   ILI9341_COLOR_BLACK
#define BLANC  ILI9341_COLOR_WHITE

static void draw_static_text(void) {
    ILI9341_Puts(145, 245, "Etat : OK", &Font_7x10, BLANC, NOIR);
    ILI9341_Puts(145, 255, "Moteur1 : Arret", &Font_7x10, BLANC, NOIR);
    ILI9341_Puts(145, 265, "Moteur2 : Arret", &Font_7x10, BLANC, NOIR);
    ILI9341_Puts(145, 275, "MPU1 : 0.0 deg", &Font_7x10, BLANC, NOIR);
    ILI9341_Puts(145, 285, "MPU2 : 0.0 deg", &Font_7x10, BLANC, NOIR);
    ILI9341_Puts(145, 295, "Asserviss : 0", &Font_7x10, BLANC, NOIR);
}

void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    ILI9341_DrawFilledRectangle(x0, y0, x1, y1, color);
}


void init_display(void) {
    ILI9341_Init();
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    Effacer_Zone(0, 0, 239, 319, NOIR);

    /* Barre verticale fixe */
    ILI9341_DrawLine(120, 50, 120, 150, BLANC);

    draw_static_text();

    sprintf(display_buffer, "Position de commande : %.1f deg", g_state.command_position);
    ILI9341_Puts(5, 305, display_buffer, &Font_7x10, BLANC, NOIR);
}

static void update_status_line(uint16_t y, const char *text) {
    Effacer_Zone(145, y, 239, y + 10, NOIR);
    ILI9341_Puts(145, y, (char *)text, &Font_7x10, BLANC, NOIR);
}

void Mettre_A_Jour_Affichage(void) {
    /* Effacer la zone dynamique sans toucher à la barre verticale */
    Effacer_Zone(20, 50, 119, 150, NOIR);
    Effacer_Zone(121, 50, 220, 150, NOIR);

    /* Calcul de la ligne horizontale pivotante */
    float rad = g_state.angle_MPU1 * M_PI / 180.0f;
    float x_r = 120.0f, y_r = 100.0f;
    float demiLongueur = 100.0f;

    float x1_0 = x_r - demiLongueur, y1_0 = y_r;
    float x2_0 = x_r + demiLongueur, y2_0 = y_r;

    float x1 = x_r + (x1_0 - x_r) * cosf(rad) - (y1_0 - y_r) * sinf(rad);
    float y1 = y_r + (x1_0 - x_r) * sinf(rad) + (y1_0 - y_r) * cosf(rad);
    float x2 = x_r + (x2_0 - x_r) * cosf(rad) - (y2_0 - y_r) * sinf(rad);
    float y2 = y_r + (x2_0 - x_r) * sinf(rad) + (y2_0 - y_r) * cosf(rad);

    ILI9341_DrawLine((uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, BLANC);

    /* Mise à jour des textes statiques */
    char buf[32];
    sprintf(buf, "Etat : %s", g_state.system_ok ? "OK" : "Erreur");
    update_status_line(245, buf);
    sprintf(buf, "Moteur1 : %s", g_state.statut_moteur1 ? "Marche" : "Arret");
    update_status_line(255, buf);
    sprintf(buf, "Moteur2 : %s", g_state.statut_moteur2 ? "Marche" : "Arret");
    update_status_line(265, buf);
    sprintf(buf, "MPU1 : %.1f deg", g_state.angle_MPU1);
    update_status_line(275, buf);
    sprintf(buf, "MPU2 : %.1f deg", g_state.angle_MPU2);
    update_status_line(285, buf);
    sprintf(buf, "Asserviss : %.2f", g_state.asservissement_value);
    update_status_line(295, buf);

    sprintf(buf, "Position de commande : %.1f deg", g_state.command_position);
    Effacer_Zone(0, 300, 120, 319, NOIR);
    ILI9341_Puts(5, 305, buf, &Font_7x10, BLANC, NOIR);
}

