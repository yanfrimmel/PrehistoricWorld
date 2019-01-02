#include "game.h"
#include "utils.h"
#include "grid.h"

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




void load_grid(SDL_Window* window, SDL_Renderer* renderer) {
    for (int x=0; x<GRID_WIDTH; ++x) {
        for (int y=0; y<GRID_HEIGHT; ++y) {
            // grid[x][y] = &0;
            // assert(grid[x][y]); // to spot if loading fails
            RecAndTexture destAndTexture = load_image_and_get_sprite_rect(renderer, SOIL_IMAGE_PATH);
            SDL_Rect dest = destAndTexture.rect;
            SDL_Texture* texture = destAndTexture.texture;
            dest.x = x*32;
            dest.y = y*32;
            SDL_RenderCopy(renderer, texture, NULL, &dest);
   
        }
    }
}

void game_loop(SDL_Window* window , SDL_Renderer* renderer,
 int window_width, int window_height) {
    // load_grid(window, renderer);
    RecAndTexture destAndTexture = load_image_and_get_sprite_rect(renderer,HUMAN_MALE_IMAGE_PATH);
    SDL_Rect dest = destAndTexture.rect;
    SDL_Texture* texture = destAndTexture.texture;
    // dest.w /= 4;
    // dest.h /= 4;

    // start sprite in center of screen
    float x_pos = (window_width - dest.w) / 2;
    float y_pos = (window_height - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    float distance = 0;
    float delta_x = 0;
    float delta_y = 0;
    int target_x = 0;
    int target_y = 0;
    Grid grid = {0};

    // grid_init()

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

        // // determine velocity toward mouse
        // int target_x = mouse_x - dest.w / 2;
        // int target_y = mouse_y - dest.h / 2;
        // float delta_x = target_x - x_pos;
        // float delta_y = target_y - y_pos;
        // float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        
        
    
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            distance = sqrt(delta_x * delta_x + delta_y * delta_y);
            target_x = mouse_x - dest.w / 2;
            target_y = mouse_y - dest.h / 2;
             if (distance > 5) {
                x_vel = delta_x * SPEED / distance;
                y_vel = delta_y * SPEED / distance;
            }
            
        }
        
        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;
        delta_x = target_x - x_pos;
        delta_y = target_y - y_pos;
        distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= window_width - dest.w) x_pos = window_width - dest.w;
        if (y_pos >= window_height - dest.h) y_pos = window_height - dest.h;

        
        if (distance < 5) {
                printf("game loop break\n");
                // break;
                x_vel = y_vel = 0;
        }
        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        // clear the window
        SDL_RenderClear(renderer);
        load_grid(window, renderer);
        // draw the image to the window
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);
        //set FPS
        SDL_Delay(1000/FPS);
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
