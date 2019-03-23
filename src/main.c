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

void must_init(bool init_ok, const char* descr){
    if(!init_ok){
        printf("couldn't initialize %s\n", descr);
        exit(1);
    }
}

// Initialize the game_context struct
int game_init(game_context** ret_context, game_config* config){ 
    game_context* context = malloc(sizeof *context);
    memset(context, 0, sizeof *context); 

    *ret_context = context;

    context->config = config;

    must_init(al_init(), "allegro"); 
    must_init(al_install_keyboard(), "keyboard");

    context->timer = al_create_timer(config->fps);
    must_init(context->timer, "timer");

    context->queue = al_create_event_queue();
    must_init(context->queue, "queue");

    context->disp = al_create_display(config->res_w, config->res_h);
    must_init(context->disp, "display");

    context->font = al_create_builtin_font();
    must_init(context->font, "font");
    
    must_init(al_init_image_addon(), "image");

    context->snek = al_load_bitmap(BTM_SNEK);
    must_init(context->snek, "snek");

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

 void render(game_context* context){
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(context->font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

    al_draw_bitmap(context->snek, 200, 200, 0);

    al_flip_display();

    context->redraw = false;
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
            render(context);
            context->redraw = false;
        }
    }

    game_destroy(context);
    context = NULL;

    return 0;
}