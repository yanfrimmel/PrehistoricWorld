#include <stdio.h>
#include "game.h"

int main( int argc, char** argv ) {
	initializeSdl();
    window = createWindow(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = createRenderer();
    printf("Pre gameLoop\n"); 
    play();
    return 0;
}

