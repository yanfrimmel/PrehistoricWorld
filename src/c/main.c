#include <stdio.h>
#include "game.h"

int main( int argc, char** argv ) {
	initialize_sdl();
    SDL_Window* window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = create_renderer(window);
    printf("Pre gameLoop\n");
    game_loop(window,renderer,WINDOW_WIDTH,WINDOW_HEIGHT);
    return 0;
}
