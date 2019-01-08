#include <stdio.h>
#include "game.h"

int main( int argc, char** argv ) {
	initialize_sdl();
    window = create_window(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = create_renderer();
    screen = SDL_GetWindowSurface(window);
    printf("Pre gameLoop\n"); 
    play();
    return 0;
}
