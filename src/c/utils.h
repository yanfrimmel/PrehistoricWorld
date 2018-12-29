#ifndef UTILS_H   /* Include guard */
#define UTILS_H

#include <stdio.h>
#include <assert.h>

void apply_function_to_all_sub_pointers(void** pointers, int size, void (*f)(void*) );

#endif 