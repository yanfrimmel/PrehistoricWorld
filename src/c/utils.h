#ifndef UTILS_H   /* Include guard */
#define UTILS_H

#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct RectAndSurface {
    SDL_Rect rect;
    SDL_Surface surface;
};
typedef struct RectAndSurface RectAndSurface;

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
RectAndSurface load_image_and_get_sprite_rect(const char *imagePath);

#endif 