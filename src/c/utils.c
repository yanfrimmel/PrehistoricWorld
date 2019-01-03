#include "utils.h"

void apply_function_to_all_sub_pointers(void** pointers, int size, void (*f)(void*) ){
    if(!pointers) {
        printf("apply_function_to_all_sub_pointers null pointer\n");
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

RecAndTexture load_image_and_get_sprite_rect(SDL_Renderer* renderer, const char *imagePath) {
    printf("load_image_and_get_sprite_rect %s\n", imagePath);
    SDL_Surface* surface = IMG_Load(imagePath);
    printf("after surface\n");
    if (!surface) {
        printf("error creating surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }
    printf("pre SDL_FreeSurface: \n");
    // load the image data into the graphics hardware's memory
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Uint32 pixelFormat;
    SDL_QueryTexture(texture, &pixelFormat, NULL, NULL, NULL);
    SDL_FreeSurface(surface);


    if (!texture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;
    printf("pre SDL_QueryTexture: \n");
    // get and scale the dimensions of texture
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    printf("destAndTexture init: \n");
    RecAndTexture destAndTexture = {dest,texture};
    return destAndTexture;
}

const char* get_image_path_string_by_tile_type(int tile_type) {
    switch (tile_type) {
        case 0:
            return &SOIL_IMAGE_PATH;
        break;
        case 1:
        break;
        case 2:
        break;
        return NULL;
    }
}
