#include "game.h"

int initialize_sdl(void) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    return 0; 
}

SDL_Window* create_window(int window_width, int window_height, int flags) {

    SDL_Window* window = SDL_CreateWindow(GAME_NAME,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       window_width, window_height,
                                       flags);
    if (!window) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return NULL;
    }
    return window;
}

SDL_Renderer* create_renderer(SDL_Window* window) { 
    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED |
                          SDL_RENDERER_PRESENTVSYNC |
                          SDL_RENDERER_TARGETTEXTURE;
                          
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer) {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return NULL;
    }

    return renderer;
}

void game_loop(SDL_Window* window , SDL_Renderer* renderer,
 int window_width, int window_height) {
    SDL_Surface* screen = SDL_CreateRGBSurface(0,window_width,window_height,32,0,0,0,0);
    int close_requested = 0;
    printf("Pre init_player \n");
    Animal human_player = init_player(window_width, window_height);
    printf("Pre grid_init \n");
    Grid grid = grid_init(renderer, window_width, window_height);

    printf("Pre gameLoop while\n");
    while (!close_requested) {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close_requested = 1;
                printf("close_requested! quiting\n");
            }
        }

        // get cursor position relative to window
        int mouse_x, mouse_y;
        int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            human_player.to_target.distance = 
            sqrt(human_player.to_target.delta_x * human_player.to_target.delta_x + 
            human_player.to_target.delta_y * human_player.to_target.delta_y);

            human_player.to_target.target_x = mouse_x - human_player.rect_and_surface.rect.w / 2;
            human_player.to_target.target_y = mouse_y - human_player.rect_and_surface.rect.h / 2;
             if (human_player.to_target.distance > IMAGE_PIXELS/2) {
                human_player.movement.x_vel = human_player.to_target.delta_x * SPEED / human_player.to_target.distance;
                human_player.movement.y_vel = human_player.to_target.delta_y * SPEED / human_player.to_target.distance;
            }
        }
        
        // update positions
        human_player.movement.x_pos += human_player.movement.x_vel / FPS;
        human_player.movement.y_pos += human_player.movement.y_vel / FPS;
        human_player.to_target.delta_x = human_player.to_target.target_x - human_player.movement.x_pos;
        human_player.to_target.delta_y = human_player.to_target.target_y - human_player.movement.y_pos;
        human_player.to_target.distance = sqrt(human_player.to_target.delta_x * human_player.to_target.delta_x + human_player.to_target.delta_y * human_player.to_target.delta_y);
        // collision detection with bounds
        if (human_player.movement.x_pos <= 0) human_player.movement.x_pos = 0;
        if (human_player.movement.y_pos <= 0) human_player.movement.y_pos = 0;
        if (human_player.movement.x_pos >= window_width - human_player.rect_and_surface.rect.w) human_player.movement.x_pos = window_width - human_player.rect_and_surface.rect.w;
        if (human_player.movement.y_pos >= window_height - human_player.rect_and_surface.rect.h) human_player.movement.y_pos = window_height - human_player.rect_and_surface.rect.h;

 
        if (human_player.to_target.distance < IMAGE_PIXELS/2) {
                printf("at target\n");
                human_player.movement.x_vel = human_player.movement.y_vel = 0;
        }
        // set the positions in the struct
        human_player.rect_and_surface.rect.y = (int) human_player.movement.y_pos;
        human_player.rect_and_surface.rect.x = (int) human_player.movement.x_pos;

        printf("Pre gameLoop grid_render\n");
        SDL_RenderClear(renderer);
        grid_render(screen, &grid, renderer);

        SDL_BlitSurface(&human_player.rect_and_surface.surface,
        NULL, screen, &human_player.rect_and_surface.rect);

        SDL_Texture* screenTexture = SDL_CreateTextureFromSurface(renderer,screen);
        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
        SDL_DestroyTexture(screenTexture);
    }
    apply_function_to_all_sub_pointers(&human_player.rect_and_surface.surface, 1, SDL_DestroyTexture);
    // SDL_DestroyTexture(&human_player.rect_and_surface.surface);
    quit_sdl(renderer, window, screen);
    return;
}

void quit_sdl(void** renderers, void** window, SDL_Surface* screen) {
    printf("quit_sdl called: quiting\n");
    destroy_human_player();
    destroy_grid_surfaces();
    destroy_grid();
    SDL_FreeSurface(screen);
    apply_function_to_all_sub_pointers(renderers, 1, SDL_DestroyRenderer);
    SDL_DestroyWindow((SDL_Renderer*)window);
    SDL_Quit();
}
