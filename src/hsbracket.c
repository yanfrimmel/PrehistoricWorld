/* This file is hsbracket.c. */
#ifdef WIN32
#include <windows.h>
#include <Rts.h>

// TODO: Make it work for windows!

// extern void __stginit_AI(void);

// BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID reserved)
// {
//   int argc = 1;
//   static char arg0[] = "libAI.dll";
//   static char *args[] = {arg0, NULL};
//   char **argv = args;
//   hs_init(&argc, &argv);
//   if (reason == DLL_PROCESS_ATTACH) {
    
//     // startupHaskell(1, args, __stginit_AI);
//     #ifdef __GLASGOW_HASKELL__
//     hs_add_root(__stginit_AI);
//     #endif
//   }
//   return TRUE;
// }


// static void ai_init() {

// }

// static void ai_exit() {
// }

#else
#include <stdlib.h>
#include <HsFFI.h>

static void ai_init(void) __attribute__((constructor));
static void ai_init() {
  int argc = 1;
  static char arg0[] = "libAI.so";
  static char *args[] = {arg0, NULL};
  char **argv = args;
  hs_init(&argc, &argv);
}

static void ai_exit(void) __attribute__((destructor));
static void ai_exit() {
  hs_exit();
}

#endif