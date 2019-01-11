#include "utils.h"

void applyFunctionToAllSubPointers(void** pointers, int size, void (*f)(void*) ){
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

SDL_Texture* loadTexture(const char *imagePath) {
    printf("pre SDL_FreeSurface: \n");
    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);
      if (!texture) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }
    return texture;
}

RectAndTexture loadImageTextureAndRectAndTexture(const char *imagePath) {
    SDL_Texture* texture = loadTexture(imagePath);
    if (!texture) {
        printf("error creating texture\n");
        SDL_Quit();
        return;
    }
    return createRectAndTexture(texture);
}

RectAndTexture createRectAndTexture(SDL_Texture* texture) {
    SDL_Rect dest;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    RectAndTexture RectAndTexture = {dest, texture};
    return RectAndTexture;
}


