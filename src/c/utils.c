#include "utils.h"

void apply_function_to_all_sub_pointers(void** pointers, void (*f)(void*) ){
    while (*pointers) {
            (*f)(*pointers);
            pointers++;
    }
}