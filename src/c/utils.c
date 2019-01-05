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

RectAndSurface load_image_and_get_sprite_rect(SDL_Renderer* renderer, const char *imagePath) {

    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        printf("error creating surface %s\n");
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }

    // // load the image data into the graphics hardware's memory
    // SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);

    // // // load the image data into the graphics hardware's memory
    // SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);

    // if (!texture) {
    //     printf("error creating texture: %s\n");
    //     SDL_DestroyRenderer(renderer);
    //     SDL_Quit();
    //     return;
    // }
    SDL_Rect dest;
    // printf("pre SDL_QueryTexture: \n");
    SDL_GetClipRect(surface, &dest);
    // SDL_QueryTexture(surface, NULL, NULL, &dest.w, &dest.h);
    // SDL_blit
    // printf("destAndTexture init: \n");
    RectAndSurface rect_and_surface = {dest,*surface};
    return rect_and_surface;
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
