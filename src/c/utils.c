#include "utils.h"

void apply_function_to_all_sub_pointers(void** pointers, int size, void (*f)(void*) ){
    if(!pointers) {
        printf("apply_function_to_all_sub_pointers null pointer\n");
        return;
    }
    printf("size = %d\n", size);
   
    for(int i = 0; i < size; i++) {
        (*f)(*pointers);
        if(i<size-1) {
            (pointers)++;
        }
    } 
}
