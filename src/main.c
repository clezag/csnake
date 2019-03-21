#include "main.h"

int config_init(game_config** ret_config){
    game_config* config = malloc(sizeof *config);
    memset(config, 0, sizeof *config); 
    *ret_config = config;

    config->fps = 1.0 / 30.0;
    config->res_h = 400;
    config->res_w = 640;
    return 0;
}

// Initialize the game_context struct
int game_init(game_context** ret_context, const game_config* config){ 
    game_context* context = malloc(sizeof *context);
    memset(context, 0, sizeof *context); 

    *ret_context = context;

    context->config = config;

    if(!al_init()){
        printf("couldn't initialize allegro\n");
        return 1;
    }

    if(!al_install_keyboard()){
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    context->timer = al_create_timer(config->fps);
    if(!context->timer){
        printf("couldn't initialize timer\n");
        return 1;
    }

    context->queue = al_create_event_queue();
    if(!context->queue){
        printf("couldn't initialize queue\n");
        return 1;
    }

    context->disp = al_create_display(config->res_w, config->res_h);
    if(!context->disp){
        printf("couldn't initialize display\n");
        return 1;
    }

    context->font = al_create_builtin_font();
    if(!context->font){
        printf("couldn't initialize font\n");
        return 1;
    }

    al_register_event_source(context->queue, al_get_keyboard_event_source());
    al_register_event_source(context->queue, al_get_display_event_source(context->disp));
    al_register_event_source(context->queue, al_get_timer_event_source(context->timer));

    context->redraw = true;

    return 0;
}

// Cleans up resources and frees the context struct
void game_destroy(game_context* context){
    al_destroy_font(context->font);
    al_destroy_display(context->disp);
    al_destroy_timer(context->timer);
    al_destroy_event_queue(context->queue); 
    free(context->config);
    context->config = NULL;
    free(context);
 }

int main(){
    int err;

    game_config* config;
    game_context* context;

    if((err = config_init(&config))){
        return err;
    }

    if((err = game_init(&context, config))){
        return err;
    }

    ALLEGRO_EVENT event;
    al_start_timer(context->timer);
    while(true){
        al_wait_for_event(context->queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            context->redraw = true;
        } else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            break;
        }

        if(context->redraw && al_is_event_queue_empty(context->queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(context->font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_flip_display();

            context->redraw = false;
        }
    }

    game_destroy(context);
    context = NULL;

    return 0;
}