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

void draw_perspective_base(void) {
    // Socle en perspective (trapeze)
    uint16_t base_y = 170;
    uint16_t base_h = 30;
    uint16_t base_w_top = 120;
    uint16_t base_w_bot = 200;
    uint16_t base_x = 120;
    // Points du trapèze
    uint16_t x1 = base_x - base_w_top/2;
    uint16_t x2 = base_x + base_w_top/2;
    uint16_t x3 = base_x + base_w_bot/2;
    uint16_t x4 = base_x - base_w_bot/2;
    uint16_t y1 = base_y;
    uint16_t y2 = base_y;
    uint16_t y3 = base_y + base_h;
    uint16_t y4 = base_y + base_h;
    ILI9341_DrawLine(x1, y1, x2, y2, BLANC);
    ILI9341_DrawLine(x2, y2, x3, y3, BLANC);
    ILI9341_DrawLine(x3, y3, x4, y4, BLANC);
    ILI9341_DrawLine(x4, y4, x1, y1, BLANC);
    // Remplissage léger (gris)
    ILI9341_DrawFilledRectangle(x1+1, y1+1, x3-1, y3-1, 0x8410);
}

void draw_perspective_vertical_bar(void) {
    // Barre verticale en perspective (du socle vers le haut)
    uint16_t base_x = 120;
    uint16_t base_y = 170;
    uint16_t top_x = 120;
    uint16_t top_y = 60;
    ILI9341_DrawLine(base_x, base_y, top_x, top_y, BLANC);
    // Socle de la barre (petit cercle)
    ILI9341_DrawFilledCircle(base_x, base_y, 6, BLANC);
}

void draw_perspective_horizontal_bar(float angle_deg) {
    // Barre horizontale pivotante en perspective (autour du sommet de la barre verticale)
    float rad = angle_deg * M_PI / 180.0f;
    float cx = 120.0f, cy = 60.0f; // sommet de la barre verticale
    float demiLongueur = 90.0f;
    // Perspective : on écrase l'axe Y
    float perspective = 0.5f;
    float x1 = cx - demiLongueur * cosf(rad);
    float y1 = cy - demiLongueur * sinf(rad) * perspective;
    float x2 = cx + demiLongueur * cosf(rad);
    float y2 = cy + demiLongueur * sinf(rad) * perspective;
    ILI9341_DrawLine((uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, ILI9341_COLOR_YELLOW);
    // Ajout d'un cercle au centre
    ILI9341_DrawFilledCircle((uint16_t)cx, (uint16_t)cy, 7, ILI9341_COLOR_RED);
}

void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    ILI9341_DrawFilledRectangle(x0, y0, x1, y1, color);
}

void init_display(void) {
    ILI9341_Init();
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    Effacer_Zone(0, 0, 239, 319, NOIR);
    // Titre du projet en haut
    ILI9341_Puts(40, 10, "DRONE 1 AXE", &Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
    // Socle et barre verticale (statique)
    draw_perspective_base();
    draw_perspective_vertical_bar();
    // Stats système en bas à droite (statique)
    char buf[32];
    uint16_t y = 245;
    sprintf(buf, "Etat : %s", g_state.system_ok ? "OK" : "Erreur");
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR); y += 10;
    sprintf(buf, "Moteur1 : %s", g_state.statut_moteur1 ? "Marche" : "Arret");
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR); y += 10;
    sprintf(buf, "Moteur2 : %s", g_state.statut_moteur2 ? "Marche" : "Arret");
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR); y += 10;
    sprintf(buf, "MPU1 : %.1f deg", g_state.angle_MPU1);
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR); y += 10;
    sprintf(buf, "MPU2 : %.1f deg", g_state.angle_MPU2);
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR); y += 10;
    sprintf(buf, "Asserviss : %.2f", g_state.asservissement_value);
    ILI9341_Puts(145, y, buf, &Font_7x10, BLANC, NOIR);
    // Angle de commande (MPU2) en bas à gauche (statique)
    sprintf(buf, "Cmd : %.1f deg", g_state.command_position);
    ILI9341_Puts(5, 305, buf, &Font_7x10, BLANC, NOIR);
    // Barre horizontale dynamique (affichée une première fois)
    draw_perspective_horizontal_bar(g_state.angle_MPU1);
}

void Mettre_A_Jour_Affichage(void) {
    // Efface uniquement la zone dynamique (autour de la barre horizontale)
    Effacer_Zone(20, 40, 220, 90, NOIR); // zone autour de la barre horizontale
    draw_perspective_horizontal_bar(g_state.angle_MPU1);
}

