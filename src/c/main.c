#include <stdio.h>
#include "game.h"
#ifdef WIN32
    #include <HsFFI.h>
#endif

int main( int argc, char** argv ) {
    //HASKELL CALL
    #ifdef WIN32
        hs_init(&argc, &argv);  
    #endif
    int i;
    i = fibonacci_hs(42);
    printf("~~~~~~~~~~~~~~~~~~~~~~~Fibonacci: %d\n", i);
    //END HASKELL CALL
	initializeSdl();
    window = createWindow(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    renderer = createRenderer();
    printf("Pre gameLoop\n"); 
    play();
    #ifdef WIN32
        hs_exit();  
    #endif
    return 0;
}

