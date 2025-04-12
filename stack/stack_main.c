#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv) {
    struct stack_t *stack = NULL;
    if(argc < 2) {
        printf("Not enough arguments");
        return 9;
    }
    for(int i=1; i<argc; i++) {
        int ret = stack_load(&stack,*(argv+i));
        if(ret == 2) {
            printf("Couldn't open file %s\n", *(argv+i));
            continue;
        }
        if(ret == 3) {
            printf("Failed to allocate memory");
            return 8;
        }
        ret = stack_save(stack,*(argv+i));
        if(ret == 2) {
            printf("Couldn't create file");
            stack_destroy(&stack);
            return 5;
        }
        printf("File %s saved\n", *(argv+i));
        stack_destroy(&stack);
    }
    return 0;
}
