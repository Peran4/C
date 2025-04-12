#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *list = dll_create();
    if(list == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    int choice, value, ret, index;
    while(1) {
        printf("What do you want to do? ");
        if(!scanf("%d", &choice)) {
            printf("Incorrect input");
            dll_clear(list);
            free(list);
            return 1;
        }
        if(choice == 0) {
            dll_clear(list);
            free(list);
            return 0;
        }
        else if(choice == 1) {
            printf("Enter a number ");
            if(!scanf("%d", &value)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            ret = dll_push_back(list,value);
            if(ret) {
                printf("Failed to allocate memory");
                dll_clear(list);
                free(list);
                return 8;
            }
        }
        else if(choice == 2) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            value = dll_pop_back(list,&ret);
            printf("%d\n", value);
        }
        else if(choice == 3) {
            printf("Enter a number ");
            if(!scanf("%d", &value)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            ret = dll_push_front(list,value);
            if(ret) {
                printf("Failed to allocate memory");
                dll_clear(list);
                free(list);
                return 8;
            }
        }
        else if(choice == 4) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            value = dll_pop_front(list,&ret);
            printf("%d\n", value);
        }
        else if(choice == 5) {
            printf("Enter a number ");
            if(!scanf("%d", &value)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            printf("Enter an index ");
            if(!scanf("%d", &index)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            ret = dll_insert(list,index,value);
            if(ret == 2) {
                printf("Failed to allocate memory");
                dll_clear(list);
                free(list);
                return 8;
            }
            if(ret) {
                printf("Index out of range\n");
            }
        }
        else if(choice == 6) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            printf("Enter an index ");
            if(!scanf("%d", &index)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            value = dll_remove(list,index,&ret);
            if(ret) {
                printf("Index out of range\n");
            }
            else {
                printf("%d\n", value);
            }
        }
        else if(choice == 7) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            value = dll_back(list,&ret);
            printf("%d\n", value);
        }
        else if(choice == 8) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            value = dll_front(list,&ret);
            printf("%d\n", value);
        }
        else if(choice == 9) {
            printf("%d\n", dll_is_empty(list));
        }
        else if(choice == 10) {
            printf("%d\n", dll_size(list));
        }
        else if(choice == 11) {
            dll_clear(list);
        }
        else if(choice == 12) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            printf("Enter an index ");
            if(!scanf("%d", &index)) {
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            else {
                value = dll_at(list,index,&ret);
                if(ret) {
                    printf("Index out of range\n");
                }
                else {
                    printf("%d\n",value);
                }
            }
        }
        else if(choice == 13) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            dll_display(list);
        }
        else if(choice == 14) {
            if(dll_is_empty(list)) {
                printf("List is empty\n");
                continue;
            }
            dll_display_reverse(list);
        }
        else {
            printf("Incorrect input data\n");
        }
    }
    return 0;
}
