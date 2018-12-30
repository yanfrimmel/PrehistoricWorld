#ifndef GAME_H   /* Include guard */
#define GAME_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define GAME_NAME ("Prehistoric World")
#define WINDOW_WIDTH (1366)
#define WINDOW_HEIGHT (768)
#define SDL_WINDOW_FULLSCREEN (0x00000001) //1 = yes
#define SPEED (150)
#define FPS (60)
#define HELLO_IMAGE_PATH ("../resources/hello.png")
#define HUMAN_MALE_IMAGE_PATH ("../resources/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("../resources/human_female.png")
#define SOIL_IMAGE_PATH ("../resources/soil.png")
#define STONES_IMAGE_PATH ("../resources/stones.png")
#define GRASS_IMAGE_PATH ("../resources/grass.png")
#define IMAGE_PIXELS (32)
#define GRID_WIDTH (WINDOW_WIDTH/IMAGE_PIXELS)
#define GRID_HEIGHT (WINDOW_HEIGHT/IMAGE_PIXELS)

int* grid[GRID_WIDTH][GRID_HEIGHT];

struct RecAndTexture {
    SDL_Rect rect;
    SDL_Texture* texture;
};
typedef struct RecAndTexture RecAndTexture;


int initialize_sdl(void);
SDL_Window* create_window(int window_width, int widow_height, int flags);  /* An example function declaration */
SDL_Renderer* create_renderer(SDL_Window* window);
RecAndTexture load_image_and_get_sprite_rect(SDL_Window* window , SDL_Renderer* renderer, const char *imagePath);
void game_loop(SDL_Window* window , SDL_Renderer* renderer , int window_width, int window_height);
void quit_sdl(void** textures, void** renderers, void** window);

#endif 