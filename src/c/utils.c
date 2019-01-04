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

RectAndTexture load_image_and_get_sprite_rect(SDL_Renderer* renderer, const char *imagePath) {
    // // load the image data into the graphics hardware's memory
    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);

    if (!texture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }
    SDL_Rect dest;
    printf("pre SDL_QueryTexture: \n");
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    printf("destAndTexture init: \n");
    RectAndTexture destAndTexture = {dest,texture};
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
