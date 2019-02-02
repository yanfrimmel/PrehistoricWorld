/* This file is hsbracket.c. */
#include </usr/lib/ghc/include/HsFFI.h>

static void my_enter(void) __attribute__((constructor));
static void my_enter(void)
{
    static char *argv[] = {"tmp/libAI.so", 0};
    #if defined(__MINGW32__)
        argv[0] = "tmp/libAI.dll";
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