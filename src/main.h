#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue; 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    bool redraw;
} game_context;

int main();

#endif