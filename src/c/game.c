#include "game.h"
#include "utils.h"
#include "grid.h"
#include "animal.h"

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

    int close_requested = 0;


    Animal human_player = {0};
    human_player.image_path = HUMAN_MALE_IMAGE_PATH;
    human_player.rect_and_texture = load_image_and_get_sprite_rect(renderer, human_player.image_path);

    human_player.movement.x_pos = (window_width - human_player.rect_and_texture.rect.w) / 2;
    human_player.movement.y_pos = (window_height - human_player.rect_and_texture.rect.h) / 2;
    human_player.movement.x_pos =  (window_width - human_player.rect_and_texture.rect.w) / 2;
    human_player.movement.y_pos =  (window_width - human_player.rect_and_texture.rect.h) / 2;
    human_player.movement.x_vel = 0;
    human_player.movement.y_vel = 0;
    
    human_player.to_target.distance = 0;
    human_player.to_target.delta_x = 0;
    human_player.to_target.delta_y = 0;
    human_player.to_target.target_x = 0;
    human_player.to_target.target_y = 0;

    // Init grid
    Grid grid = {0};

    // Set grid dimensions
    grid.rect.w = window_width;
    grid.rect.h = window_height;

    // Adjust size and center
    grid_alignCenter(&grid, window_width, window_height);

    if(!grid_init(renderer, &grid))
    {
        fprintf(stderr, "Grid fail to initialize !\n");
        return false;
    }
    printf("Pre gameLoop while\n");
    // animation loop
    grid_render(&grid, renderer);
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

            human_player.to_target.target_x = mouse_x - human_player.rect_and_texture.rect.w / 2;
            human_player.to_target.target_y = mouse_y - human_player.rect_and_texture.rect.h / 2;
             if (human_player.to_target.distance > 5) {
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
        if (human_player.movement.x_pos >= window_width - human_player.rect_and_texture.rect.w) human_player.movement.x_pos = window_width - human_player.rect_and_texture.rect.w;
        if (human_player.movement.y_pos >= window_height - human_player.rect_and_texture.rect.h) human_player.movement.y_pos = window_height - human_player.rect_and_texture.rect.h;

        
        if (human_player.to_target.distance < 5) {
                printf("game loop break\n");
                human_player.movement.x_vel = human_player.movement.y_vel = 0;
        }
        // set the positions in the struct
        human_player.rect_and_texture.rect.y = (int) human_player.movement.y_pos;
        human_player.rect_and_texture.rect.x = (int) human_player.movement.x_pos;

        printf("Pre gameLoop grid_render\n");
        render_adjacent_tiles(grid,renderer, human_player.rect_and_texture.rect);
       
        SDL_RenderCopy(renderer, human_player.rect_and_texture.texture, NULL, &human_player.rect_and_texture.rect);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000/FPS);
    }
    apply_function_to_all_sub_pointers(human_player.rect_and_texture.texture, 1, SDL_DestroyTexture);
    destroy_grid_textures(grid);
    quit_sdl(renderer, window);
    return;
}

void render_adjacent_tiles(Grid grid, SDL_Renderer* renderer, SDL_Rect dest) {
    int x = dest.x/IMAGE_PIXELS;
    int y = dest.y/IMAGE_PIXELS;
    //check over
    int right = x+1 < grid.xTiles ? x+1 : x;
    int left  = x-1 >= 0 ? x-1 : 0;
    int down = y+1 < grid.yTiles ? y+1 : y;
    int up  = y-1 >= 0 ? y-1 : 0;

    grid_render_tile(&grid.tiles[x][y], renderer);
    grid_render_tile(&grid.tiles[right][y], renderer);
    grid_render_tile(&grid.tiles[left][y], renderer);
    grid_render_tile(&grid.tiles[x][down], renderer);
    grid_render_tile(&grid.tiles[x][up], renderer);
    grid_render_tile(&grid.tiles[right][up], renderer);
    grid_render_tile(&grid.tiles[right][down], renderer);
    grid_render_tile(&grid.tiles[left][down], renderer);
    grid_render_tile(&grid.tiles[left][up], renderer);
}

// void quit_sdl(SDL_Texture** textures, SDL_Renderer** renderers, SDL_Window* window) {
void quit_sdl(void** renderers, void** window) {
    printf("quit_sdl called: quiting\n");
    // clean up resources before exiting
    apply_function_to_all_sub_pointers(renderers, 1, SDL_DestroyRenderer);
    SDL_DestroyWindow((SDL_Renderer*)window);
    SDL_Quit();
}
