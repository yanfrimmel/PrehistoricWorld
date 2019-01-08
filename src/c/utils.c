#include "utils.h"

void apply_functionToAllSubPointers(void** pointers, int size, void (*f)(void*) ){
    if(!pointers) {
        printf("apply_functionToAllSubPointers null pointer\n");
        return;
    }
    printf("size = %d\n", size);
   
    for(int i = 0; i < size; i++) {
        (*f)(*pointers);
        if(i<size-1) {
            (pointers)++;
        }
    } 
}

RectAndSurface loadImageAndGetSpriteRect(const char *imagePath) {

    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        printf("error creating surface\n");
        // SDL_Quit();
        return;
    }
    SDL_Rect dest;
    SDL_GetClipRect(surface, &dest);
    RectAndSurface rectAndSurface = {dest,*surface};
    return rectAndSurface;
}


