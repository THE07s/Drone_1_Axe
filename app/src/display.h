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

void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Dessiner_Ligne(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Mettre_A_Jour_Affichage(void);

#endif /* DISPLAY_H_ */
