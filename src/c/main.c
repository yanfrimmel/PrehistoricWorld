#include <stdio.h>
#include "graphical_api.h"

#define WINDOW_WIDTH (1366)
#define WINDOW_HEIGHT (768)
#define SDL_WINDOW_FULLSCREEN (0x00000001) //1 = yes

int main( int argc, char** argv ) {
	initialize_sdl();
    SDL_Window* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = createRenderer(window);
    printf("Pre gameLoop\n");
    gameLoop(window,renderer,WINDOW_WIDTH,WINDOW_HEIGHT);
    return 0;
}
