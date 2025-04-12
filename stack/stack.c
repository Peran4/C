#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_push(struct stack_t **stack, char *value) {
    if(stack == NULL || value == NULL) {
        return 1;
    }
    struct stack_t *tmp = malloc(sizeof(struct stack_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->prev = *stack;
    tmp->sentence = value;
    *stack = tmp;
    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code) {
    if(stack == NULL || *stack == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }
    char *value = (*stack)->sentence;
    struct stack_t *tmp = *stack;
    *stack = (*stack)->prev;
    free(tmp);
    if(err_code != NULL) {
        *err_code = 0;
    }
    return value;
}

void stack_destroy(struct stack_t **stack) {
    if(stack == NULL || *stack == NULL) {
        return;
    }

    while(*stack != NULL) {
        char* tmp = stack_pop(stack,NULL);
        if(tmp != NULL) {
            free(tmp);
        }
    }
}

int stack_load(struct stack_t **stack, const char *filename) {
    if(stack == NULL || filename == NULL || *stack != NULL) {
        return 1;
    }
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        return 2;
    }
    char c;
    int flag=0;

    while(1) {
        int len=0;
        while(1) {
            c = (char)fgetc(f);
            len++;
            if(c == EOF) {
                flag = 1;
                break;
            }
            if(c == '.') {
                break;
            }
        }
        if(flag) {
            break;
        }
        fseek(f,-len,SEEK_CUR);
        struct stack_t *tmp = malloc(sizeof(struct stack_t));
        if(tmp == NULL) {
            stack_destroy(stack);
            fclose(f);
            return 3;
        }
        tmp->prev = *stack;
        *stack = tmp;
        tmp->sentence = malloc(sizeof(char) * (len+1));
        if(tmp->sentence == NULL) {
            stack_destroy(stack);
            fclose(f);
            return 3;
        }
        for(int i=0; i<len; i++) {
            *(tmp->sentence+i) = (char)fgetc(f);
        }
        *(tmp->sentence+len) = '\0';
    }
    fclose(f);
    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename) {
    if(stack == NULL || filename == NULL) {
        return 1;
    }
    FILE *f = fopen(filename,"w");
    if(f == NULL) {
        return 2;
    }
    struct stack_t *tmp = (struct stack_t *)stack;
    while(tmp != NULL) {
        fprintf(f,"%s", tmp->sentence);
        tmp = tmp->prev;
    }
    fclose(f);
    return 0;
}

