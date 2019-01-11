#ifndef UTILS_H   /* Include guard */
#define UTILS_H

#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define IMAGE_PIXELS (32.0)

struct RectAndTexture {
    SDL_Rect rect;
    SDL_Texture* texture;
};
typedef struct RectAndTexture RectAndTexture;

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
RectAndTexture loadImageTextureAndRectAndTexture(const char *imagePath);
RectAndTexture createRectAndTexture(SDL_Texture* texture);
SDL_Texture* loadTexture(const char *imagePath);

SDL_Window* window;
SDL_Renderer* renderer;

#endif 