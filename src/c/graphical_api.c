#include <stdio.h>
#include <math.h>

#include "graphical_api.h"
#include "utils.h"


int initialize_sdl(void) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

SDL_Window* createWindow(int window_width, int window_height, int flags) {

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

SDL_Renderer* createRenderer(SDL_Window* window) { 
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

void gameLoop(SDL_Window* window , SDL_Renderer* renderer , int window_width, int window_height) {
    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load(HELLO_IMAGE_STRING);
    if (!surface) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;

    // start sprite in center of screen
    float x_pos = (window_width - dest.w) / 2;
    float y_pos = (window_height - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    // animation loop
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

        // determine velocity toward mouse
        int target_x = mouse_x - dest.w / 2;
        int target_y = mouse_y - dest.h / 2;
        float delta_x = target_x - x_pos;
        float delta_y = target_y - y_pos;
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        
        // prevent jitter
        if (distance < 5) {
            printf("game loop break\n");
            break;
            x_vel = y_vel = 0;
        }
        else {
            x_vel = delta_x * SPEED / distance;
            y_vel = delta_y * SPEED / distance;
        }

        // reverse velocity if mouse button 1 pressed
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            x_vel = -x_vel;
            y_vel = -y_vel;
        }
        
        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= window_width - dest.w) x_pos = window_width - dest.w;
        if (y_pos >= window_height - dest.h) y_pos = window_height - dest.h;

        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        
        // clear the window
        SDL_RenderClear(renderer);

        // draw the image to the window
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    quit_sdl(texture, renderer, window);
    return;
}

// void quit_sdl(SDL_Texture** textures, SDL_Renderer** renderers, SDL_Window* window) {
void quit_sdl(void** textures, void** renderers, void** window) {
    printf("quit_sdl called: quiting\n");
    // clean up resources before exiting
    apply_function_to_all_sub_pointers(textures, 1, SDL_DestroyTexture);
    apply_function_to_all_sub_pointers(renderers, 1, SDL_DestroyRenderer);
    SDL_DestroyWindow((SDL_Renderer*)window);
    SDL_Quit();
}
