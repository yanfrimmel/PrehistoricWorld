#include <stdio.h>
#include "game.h"

int main( int argc, char** argv ) {
    //HASKELL CALL
    printf("start hs_init: \n");
    // hs_init(&argc, &argv);
    int i;
    i = fibonacci_hs(42);
    printf("~~~~~~~~~~~~~~~~~~~~~~~Fibonacci: %d\n", i);
    //END HASKELL CALL
	initializeSdl();
    window = createWindow(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = createRenderer();
    printf("Pre gameLoop\n"); 
    play();
    return 0;
}

