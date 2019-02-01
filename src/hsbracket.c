/* This file is hsbracket.c. */
#include </usr/lib/ghc/include/HsFFI.h>

static void my_enter(void) __attribute__((constructor));
static void my_enter(void)
{
    static char *argv[] = {"tmp/libAI.so", 0};
    #if defined(__MINGW32__)
        argv[0] = "tmp/libAI.dll.so";
    #endif
    static char **argv_ = argv;
    static int argc = 1;
    hs_init(&argc, &argv_);
}

static void my_exit(void) __attribute__((destructor));
static void my_exit(void)
{
    hs_exit();
}
//ghc -O2 -dynamic -shared -fPIC -o libAI.so AI.hs  hsbracket.c -lHSrts_thr-ghc8.0.2
//gcc -O2 -c `sdl2-config --libs --cflags` -lSDL2_image ./*.c
//gcc -o Pre main.o game.o utils.o grid.o animal.o `sdl2-config --libs --cflags` -lSDL2_image -lm -L. -lAI -Wl,-rpath,'$ORIGIN'

//cd tmp
//ghc -O2 -dynamic -shared -fPIC -o libAI.so ../src/haskell/AI.hs  ../src/hsbracket.c -lHSrts_thr-ghc8.0.2
//gcc -O2 -c `sdl2-config --libs --cflags` -lSDL2_image ../src/c/*.c
//gcc -o ../Pre4 main.o game.o utils.o grid.o animal.o `sdl2-config --libs --cflags` -lSDL2_image -lm -L. -lAI -Wl,-rpath,'$ORIGIN/tmp'