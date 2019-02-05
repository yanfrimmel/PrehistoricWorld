#ifdef WIN32
    #include <Rts.h>
    void HsStart() {
       int argc = 1;
       char* argv[] = {"ghcDll", NULL}; // argv must end with NULL

       // Initialize Haskell runtime
       char** args = argv;
       hs_init(&argc, &args);
    }
    void HsEnd() {
       hs_exit();
    }
#else
    #include <stdlib.h>
    #include "HsFFI.h"
        // This works for GHC 8.0.2
        // HsBool HsStart(void) __attribute__((constructor));
        HsBool HsStart(void) {
          int argc = 2;
          char *argv[] = { "+RTS", "-A32m", NULL };
          char **pargv = argv;

          // Initialize Haskell runtime
          hs_init(&argc, &pargv);

          // do any other initialization here and
          // return false if there was a problem
          return HS_BOOL_TRUE;
        }

        // void HsEnd(void) __attribute__((destructor));
        void HsEnd(void) {
          hs_exit();
        }
#endif