#ifndef DISPLAY_H_
#define DISPLAY_H_

#define ILI9341_HEIGHT  240
#define ILI9341_WIDTH   320
 
#include "../config.h"
#include "../drivers/bsp/tft_ili9341/stm32g4_ili9341.h"
#include "sensors.h"
#include "state.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

void init_display(void);
void Effacer_Zone(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Mettre_A_Jour_Affichage(void);
void draw_perspective_base(void);
void draw_vertical_bar(void);
void draw_horizontal_bar(float angle_deg);
void draw_title(void);

#endif /* DISPLAY_H_ */
