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

RectAndSurface load_image_and_get_sprite_rect(const char *imagePath) {

    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        printf("error creating surface\n");
        // SDL_Quit();
        return;
    }
    SDL_Rect dest;
    SDL_GetClipRect(surface, &dest);
    RectAndSurface rect_and_surface = {dest,*surface};
    return rect_and_surface;
}

const char* get_image_path_string_by_tile_type(int tile_type) {
    switch (tile_type) {
        case 0:
            return SOIL_IMAGE_PATH;
        break;
        case 1:
        break;
        case 2:
        break;
        return NULL;
    }
}
