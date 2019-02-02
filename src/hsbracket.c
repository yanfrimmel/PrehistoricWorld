/* This file is hsbracket.c. */
#include <HsFFI.h>
#include <stdio.h>
#include <Rts.h>

static void my_enter(void) __attribute__((constructor));
static void my_enter(void)
{
    static char *argv[] = {"", 0};
    #if defined(__MINGW32__)
        argv[0] = "libAI.dll";
    #else
        argv[0] = "libAI.so";
    #endif
    static char **argv_ = argv;
    static int argc = 1;
    hs_init(&argc, &argv_);
    printf("passed hs_init: argv[0]: %s\n", argv[0]);
}

static void my_exit(void) __attribute__((destructor));
static void my_exit(void)
{
    printf("hs_exit\n");
    hs_exit();
}