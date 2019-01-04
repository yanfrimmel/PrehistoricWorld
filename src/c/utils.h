#ifndef UTILS_H   /* Include guard */
#define UTILS_H

#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define HELLO_IMAGE_PATH ("../resources/hello.png")
#define HUMAN_MALE_IMAGE_PATH ("../resources/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("../resources/human_female.png")
#define SOIL_IMAGE_PATH ("../resources/soil.png")
#define STONES_IMAGE_PATH ("../resources/stones.png")
#define GRASS_IMAGE_PATH ("../resources/grass.png")

struct RectAndTexture {
    SDL_Rect rect;
    SDL_Texture* texture;
};
typedef struct RectAndTexture RectAndTexture;

struct DistanceFromTarget {
    float distance;
    float delta_x;
    float delta_y;
    int target_x;
    int target_y;
};
typedef struct DistanceFromTarget DistanceFromTarget;

struct Movement {
    float x_pos; 
    float y_pos;
    float x_vel;
    float y_vel;
};
typedef struct Movement Movement;

void apply_function_to_all_sub_pointers(void** pointers, int size, void (*f)(void*) );
RectAndTexture load_image_and_get_sprite_rect(SDL_Renderer* renderer, const char *imagePath);
const char* get_image_path_string_by_tile_type(int tile_type);

#endif 