/**
 * @file display.c
 * @brief Implémentation du module de gestion de l'affichage
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#include "display.h"

// Variables globales
char display_buffer[32];  /*!< Buffer pour les strings affichés */
static float old_x1 = 0, old_y1 = 0, old_x2 = 0, old_y2 = 0; /*!< Anciennes coordonnées de la barre horizontale */


void draw_base(void) {
    // Base
    uint16_t base_y = 170;
    uint16_t base_h = 30;
    uint16_t base_w_top = 100;
    uint16_t base_w_bot = 150;
    uint16_t base_x = ILI9341_WIDTH / 2;

    // Points du trapèze
    uint16_t x1 = base_x - base_w_top/2;
    uint16_t x2 = base_x + base_w_top/2;
    uint16_t x3 = base_x + base_w_bot/2;
    uint16_t x4 = base_x - base_w_bot/2;
    uint16_t y1 = base_y;
    uint16_t y2 = base_y;
    uint16_t y3 = base_y + base_h;
    uint16_t y4 = base_y + base_h;
    ILI9341_DrawLine(x1, y1, x2, y2, ILI9341_COLOR_WHITE);
    ILI9341_DrawLine(x2, y2, x3, y3, ILI9341_COLOR_WHITE);
    ILI9341_DrawLine(x3, y3, x4, y4, ILI9341_COLOR_WHITE);
    ILI9341_DrawLine(x4, y4, x1, y1, ILI9341_COLOR_WHITE);

    // Remplissage léger (gris) du trapèze (ChatGPT)
    for (uint16_t y = y1 + 1; y < y3; y++) {
        // Interpolation linéaire pour trouver les bords gauche et droit à chaque ligne
        float t = (float)(y - y1) / (float)(y3 - y1);
        int16_t left = (int16_t)(x1 + 1 + t * (x4 - x1));
        int16_t right = (int16_t)(x2 + t * (x3 - x2));
        if (right > left) {
            ILI9341_DrawLine(left, y, right, y, 0x8410);
        }
    }
}

void draw_vertical_bar(void) {
    uint16_t base_x = ILI9341_WIDTH / 2;
    uint16_t base_y = 185;
    uint16_t top_x = ILI9341_WIDTH / 2;
    uint16_t top_y = 80;
    ILI9341_DrawLine(base_x, base_y, top_x, top_y, ILI9341_COLOR_WHITE);

    ILI9341_DrawFilledCircle(base_x, base_y, 7, ILI9341_COLOR_WHITE);
}

void draw_horizontal_bar(float angle_deg) {
    float demiLongueur = 90.0f;

    float cx = ILI9341_WIDTH / 2.0f;
    float cy = 80.0f;

    float rad = angle_deg * M_PI / 180.0f;
    float cos_a = cosf(rad);
    float sin_a = sinf(rad);

    float x1 = cx - demiLongueur * cos_a;
    float y1 = cy - demiLongueur * sin_a;
    float x2 = cx + demiLongueur * cos_a;
    float y2 = cy + demiLongueur * sin_a;
    
    ILI9341_DrawLine((uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, ILI9341_COLOR_YELLOW | 0x4000);

    ILI9341_DrawFilledCircle((uint16_t)cx, (uint16_t)cy, 7, ILI9341_COLOR_RED);
    old_x1 = x1; old_y1 = y1; old_x2 = x2; old_y2 = y2;
}

void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    ILI9341_DrawFilledRectangle(x0, y0, x1, y1, color);
}

void draw_stats_texte(void) {
    const uint16_t stats_larg = 119;
    const uint16_t stats_ligne = 10;
    const uint16_t stats_nblignes = 6;
    const uint16_t stats_espacement = 2;
    const uint16_t stats_hauteur = stats_nblignes * (stats_ligne + stats_espacement) + 4;
    const uint16_t stats_x = ILI9341_WIDTH - stats_larg - 2;
    const uint16_t stats_y = ILI9341_HEIGHT - stats_hauteur - 2;
    uint16_t y = stats_y + 2;
    ILI9341_Puts(stats_x + 6, y, "Etat :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    ILI9341_Puts(stats_x + 6, y, "Moteur1 :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    ILI9341_Puts(stats_x + 6, y, "Moteur2 :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    ILI9341_Puts(stats_x + 6, y, "MPU1 :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    ILI9341_Puts(stats_x + 6, y, "MPU2 :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    ILI9341_Puts(stats_x + 6, y, "Asserv :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void update_stats_valeurs(void) {
    char buf[16];
    const uint16_t stats_larg = 119;
    const uint16_t stats_ligne = 10;
    const uint16_t stats_nblignes = 6;
    const uint16_t stats_espacement = 2;
    const uint16_t stats_hauteur = stats_nblignes * (stats_ligne + stats_espacement) + 4;
    const uint16_t stats_x = ILI9341_WIDTH - stats_larg - 2;
    const uint16_t stats_y = ILI9341_HEIGHT - stats_hauteur - 2;
    uint16_t value_x = stats_x;
    uint16_t y = stats_y + 2;
    // Etat
    value_x = stats_x + 49;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%s", g_state.system_ok ? "OK" : "ERR");
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    // Moteur1
    value_x = stats_x + 70;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%s", g_state.statut_moteur1 ? "ON" : "OFF");
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    // Moteur2
    value_x = stats_x + 70;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%s", g_state.statut_moteur2 ? "ON" : "OFF");
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    // MPU1
    value_x = stats_x + 49;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%.1f deg", g_state.angle_MPU1);
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    // MPU2
    value_x = stats_x + 49;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%.1f deg", g_state.command_position);
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK); y += stats_ligne + stats_espacement;
    // Asserv
    value_x = stats_x + 63;
    ILI9341_DrawFilledRectangle(value_x, y, stats_x + stats_larg - 4, y + stats_ligne, ILI9341_COLOR_BLACK);
    sprintf(buf, "%.2f", g_state.asservissement_value);
    ILI9341_Puts(value_x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}

void draw_angle_command_texte(void) {
    uint16_t x = 2;
    uint16_t y = ILI9341_HEIGHT - 10 - 2;
    ILI9341_Puts(x, y, "Cmd :", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
}

void update_angle_command_valeurs(void) {
    char buf[16];
    uint16_t x = 2 + 38;
    uint16_t y = ILI9341_HEIGHT - 10 - 2;

    ILI9341_DrawFilledRectangle(x, y, x + 60, y + 10, ILI9341_COLOR_RED);
    sprintf(buf, "%.1f deg", g_state.command_position);
    ILI9341_Puts(x, y, buf, &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
}

void draw_stats(void) {
    // Affiche le fond, le cadre, les labels et les valeurs initiales
    const uint16_t stats_larg = 119;
    const uint16_t stats_nblignes = 6;
    const uint16_t stats_ligne = 10;
    const uint16_t stats_espacement = 2;
    const uint16_t stats_hauteur = stats_nblignes * (stats_ligne + stats_espacement) + 4;
    const uint16_t stats_x = ILI9341_WIDTH - stats_larg - 2;
    const uint16_t stats_y = ILI9341_HEIGHT - stats_hauteur - 2;
    // Fond noir
    ILI9341_DrawFilledRectangle(stats_x, stats_y, stats_x + stats_larg, stats_y + stats_hauteur, ILI9341_COLOR_BLACK);
    // Cadre blanc
    ILI9341_DrawRectangle(stats_x, stats_y, stats_x + stats_larg, stats_y + stats_hauteur, ILI9341_COLOR_WHITE);
    draw_stats_texte();
    update_stats_valeurs();
}

void draw_angle_command(void) {
    draw_angle_command_texte();
    update_angle_command_valeurs();
}

void draw_title(void) {
    char* titre = "DRONE 1 AXE";
    uint16_t titre_largeur = 0, titre_hauteur = 0;
    ILI9341_GetStringSize(titre, &Font_11x18, &titre_largeur, &titre_hauteur);
    uint16_t titre_x = (ILI9341_WIDTH - titre_largeur) / 2;
    ILI9341_Puts(titre_x, 2, titre, &Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
}

void init_display(void) {
    ILI9341_Init();
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    ILI9341_Fill(ILI9341_COLOR_BLACK);
    draw_title();
    draw_base();
    draw_vertical_bar();
    draw_stats();
    draw_angle_command();
    draw_horizontal_bar(g_state.angle_MPU1);
}

void update_affichage(void) {
    ILI9341_DrawLine((uint16_t)old_x1, (uint16_t)old_y1, (uint16_t)old_x2, (uint16_t)old_y2, ILI9341_COLOR_BLACK);
    if (g_state.angle_MPU1 > 80.0f || g_state.angle_MPU1 < -80.0f) {
        draw_vertical_bar();
        draw_title();
    } else if (g_state.angle_MPU1 > 44.5f || g_state.angle_MPU1 < -44.5f) {
        draw_title();
    }
    draw_horizontal_bar(g_state.angle_MPU1);
    update_stats_valeurs();
    update_angle_command_valeurs();
}