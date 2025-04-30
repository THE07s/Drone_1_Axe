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

// Initialisation de l'écran
void init_display(void);

// Affichage de l'angle d'inclinaison
void display_angle(int x,int y);

// Affichage de la ligne d'inclinaison
void display_inclination_line(int x1, int y1, int x2, int y2);

// Effacement de l'écran ou d'une zone
void clear_display(void);

// Autres fonctions selon les besoins

#endif /* DISPLAY_H_ */
