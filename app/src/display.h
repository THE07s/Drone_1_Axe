/**
 * @file display.h
 * @brief Module de gestion de l'affichage
 * 
 * @author Loïc LEENAERTS (https://github.com/THE07s)
 * @author Romain PICAULT (https://github.com/RomainPICAULT)
 * @date 13 juin 2025
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define ILI9341_HEIGHT  240  /*!< Hauteur de l'écran en pixels */
#define ILI9341_WIDTH   320  /*!< Largeur de l'écran en pixels */
 
#include "../config.h"
#include "../drivers/bsp/tft_ili9341/stm32g4_ili9341.h"
#include "state.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>

/**
 * @brief Initialise le module d'affichage
 * 
 * @pre L'écran TFT doit être correctement connecté
 * @post L'écran est prêt pour l'affichage des données dynamiques
 */
void init_display(void);

/**
 * @brief Efface une zone rectangulaire de l'écran
 * 
 * @param x0 Coordonnée X du coin supérieur gauche
 * @param y0 Coordonnée Y du coin supérieur gauche  
 * @param x1 Coordonnée X du coin inférieur droit
 * @param y1 Coordonnée Y du coin inférieur droit
 * @param color Couleur de remplissage
 */
void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * @brief Met à jour l'affichage complet
 * 
 * Actualise tous les éléments dynamiques de l'écran (horizon, statistiques, etc.)
 */
void update_affichage(void);

/**
 * @brief Dessine la base de l'horizon artificiel
 * 
 * Affiche un trapèze représentant la base de l'horizon artificiel.
 */
void draw_base(void);

/**
 * @brief Dessine la barre verticale de l'horizon artificiel
 * 
 * Affiche la ligne verticale fixe au centre de l'horizon artificiel.
 */
void draw_vertical_bar(void);

/**
 * @brief Dessine la barre horizontale de l'horizon artificiel
 * 
 * Affiche la ligne horizontale mobile représentant l'inclinaison du drone.
 * 
 * @param angle_deg Angle d'inclinaison en degrés
 */
void draw_horizontal_bar(float angle_deg);

/**
 * @brief Dessine le titre de l'application
 * 
 * Affiche le titre "Drone 1 Axe" en haut de l'écran.
 */
void draw_title(void);

#endif /* DISPLAY_H_ */
