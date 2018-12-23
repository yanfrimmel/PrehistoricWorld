#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "../../src/c/utils.h"

void string_edit_function(char* word){
   word[0] = 'b';
   word[1] = 'a';
   word[2] = 'a';
}

void test_apply_function_to_all_sub_pointers(void) {
    puts("test_apply_function_to_all_sub_pointers: ");
    char *word;
    char **sentence;

    //fill data structure
    word = malloc(4 * sizeof *word); // assume it worked
    strcpy(word, "foo");

    sentence = malloc(4 * sizeof *sentence); // assume it worked
    sentence[0] = word;
    sentence[1] = word;
    sentence[2] = word;
    sentence[3] = NULL;

    assert(sentence[0][0] == 'f');
    assert(sentence[0][1] == 'o');
    assert(sentence[0][2] == 'o');

    apply_function_to_all_sub_pointers((char*)sentence, string_edit_function);

    assert(sentence[0][0] == 'b');
    assert(sentence[0][1] == 'a');
    assert(sentence[0][2] == 'a');

    free(sentence);
    free(word);
    puts("test_apply_function_to_all_sub_pointers: passed");
}

int main() {
	test_apply_function_to_all_sub_pointers();
}
