#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "../../src/c/utils.h"
/**
 * functions are static since I don't use headers for test files -
 * static makes the function to be defined once,
 * and not in every file that uses the same function
 */
static void change_array_element_function(int* num){
    printf("*num = %d\n", *num);
    (*num)++;
}

static void testApplyFunctionToAllSubPointers(void) {
    puts("applyFunctionToAllSubPointers: ");
    int **doublePointer = malloc (3* sizeof(int*));
    int x = 1;
    int y = 2;
    int z = 3;
    int *one = &x;
    int *two = &y;
    int *three = &z;
    printf("doublePointer[0]: %d\n", &one);
    doublePointer[0] = one;
    doublePointer[1] = two; 
    doublePointer[2] = three; 

    // assert(array[0] == 1);
    // assert(array[1] == 2);
    applyFunctionToAllSubPointers(doublePointer, 3, change_array_element_function);
    printf("doublePointer[0]: %d\n", *doublePointer[0]);
    assert(*doublePointer[0] == 2);
    assert(*doublePointer[1] == 3);
    assert(*doublePointer[2] == 4);
    
    free(doublePointer);
    puts("test_apply_function_to_all_sub_pointers: passed");
}