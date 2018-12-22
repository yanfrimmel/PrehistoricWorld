#include "utils.h"
#include <stdio.h>

void apply_function_to_all_sub_pointers(void** pointers, void (*f)(void*) ){
    printf("pointers: %d", *pointers);

    while (*pointers) {
            printf("pointers: %d", *pointers);
            (*f)(*pointers);
            pointers++;
    }
}