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
    float deltaX;
    float deltaY;
    int targetX;
    int targetY;
};
typedef struct DistanceFromTarget DistanceFromTarget;

struct Movement {
    float xPos; 
    float yPos;
    float xVel;
    float yVel;
};
typedef struct Movement Movement;

void apply_functionToAllSubPointers(void** pointers, int size, void (*f)(void*) );
RectAndSurface loadImageAndGetSpriteRect(const char *imagePath);

#endif 