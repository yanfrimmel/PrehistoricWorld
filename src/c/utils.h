#ifndef UTILS_H   /* Include guard */
#define UTILS_H

void apply_function_to_all_sub_pointers(void** pointers, int size, void (*f)(void*) );

#endif 