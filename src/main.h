#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "resources.h"

typedef struct {
    uint16_t res_w;
    uint16_t res_h;
    double fps; 
} game_config;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue; 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_BITMAP* snek;
    bool redraw;
    game_config* config;
} game_context;

int main();

#endif