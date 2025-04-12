#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create() {
    struct doubly_linked_list_t *list = malloc(sizeof(struct doubly_linked_list_t));
    if(list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        return 1;
    }
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->data = value;

    if(dll_is_empty(dll)) {
        tmp->next = NULL;
        tmp->prev = NULL;
        dll->head = tmp;
        dll->tail = tmp;
        return 0;
    }
    dll->tail->next = tmp;
    tmp->prev = dll->tail;
    tmp->next = NULL;
    dll->tail = tmp;
    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        return 1;
    }
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->data = value;

    if(dll_is_empty(dll)) {
        tmp->next = NULL;
        tmp->prev = NULL;
        dll->head = tmp;
        dll->tail = tmp;
        return 0;
    }
    dll->head->prev = tmp;
    tmp->next = dll->head;
    tmp->prev = NULL;
    dll->head = tmp;
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->head == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 0;
    }
    struct node_t *tmp = dll->head;
    int value = tmp->data;
    dll->head = dll->head->next;
    if(dll->head != NULL) {
        dll->head->prev = NULL;
    }
    else {
        dll->tail = NULL;
    }
    free(tmp);
    if(err_code != NULL) {
        *err_code = 0;
    }
    return value;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->tail == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 0;
    }
    struct node_t *tmp = dll->tail;
    int value = tmp->data;
    dll->tail = dll->tail->prev;
    if(dll->tail != NULL) {
        dll->tail->next = NULL;
    }
    else {
        dll->head = NULL;
    }
    free(tmp);
    if(err_code != NULL) {
        *err_code = 0;
    }
    return value;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->tail == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 0;
    }
    if(err_code != NULL) {
        *err_code = 0;
    }
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->head == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 0;
    }
    if(err_code != NULL) {
        *err_code = 0;
    }
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->head == NULL) {
        return NULL;
    }
    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL) || dll->tail == NULL) {
        return NULL;
    }
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        return -1;
    }
    if(dll->tail == NULL && dll->head == NULL) {
        return 0;
    }
    struct node_t *tmp = dll->head;
    int i=1;
    while(tmp->next != NULL) {
        i++;
        tmp = tmp->next;
    }
    return i;
}

int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        return -1;
    }
    if(dll->tail == NULL && dll->head == NULL) {
        return 1;
    }
    return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }

    struct node_t *tmp = dll->head;
    unsigned int i=0;
    while(tmp != NULL) {
        if(index == i) {
            if(err_code != NULL) {
                *err_code = 0;
            }
            return tmp->data;
        }
        i++;
        tmp = tmp->next;
    }
    if(err_code != NULL) {
        *err_code = 1;
    }
    return -1;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        return 1;
    }
    struct node_t *aft = dll->head;
    struct node_t *bef = NULL;
    unsigned int i=0;
    while(aft != NULL) {
        if(index == i) {
            break;
        }
        i++;
        bef = aft;
        aft = aft->next;
    }
    if(aft == NULL && i != index) {
        return 1;
    }
    if(bef == NULL) {
        int ret = dll_push_front(dll,value);
        if(ret) {
            return 2;
        }
        return 0;
    }
    if(aft == NULL) {
        int ret = dll_push_back(dll,value);
        if(ret) {
            return 2;
        }
        return 0;
    }
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->data = value;
    tmp->prev = bef;
    bef->next = tmp;
    tmp->next = aft;
    aft->prev = tmp;
    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if(dll == NULL || (dll->tail == NULL && dll->head != NULL) || (dll->head == NULL && dll->tail != NULL)) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }

    struct node_t *tmp = dll->head;
    unsigned int i=0;
    while(tmp != NULL) {
        if(index == i) {
            break;
        }
        i++;
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }
    int value = tmp->data;
    if(tmp->prev != NULL) {
        tmp->prev->next = tmp->next;
    }
    if(tmp->next != NULL) {
        tmp->next->prev = tmp->prev;
    }
    if(tmp == dll->head) {
        dll->head = tmp->next;
    }
    if(tmp == dll->tail) {
        dll->tail = tmp->prev;
    }
    free(tmp);
    if(err_code != NULL) {
        *err_code = 0;
    }
    return value;
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL || dll->tail == NULL) {
        return;
    }
    while(!dll_is_empty(dll)) {
        dll_pop_front(dll,NULL);
    }
}

void dll_display(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL || dll->tail == NULL) {
        return;
    }
    struct node_t *tmp = dll->head;
    while(tmp != NULL) {
        printf("%d ",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL || dll->tail == NULL) {
        return;
    }
    struct node_t *tmp = dll->tail;
    while(tmp != NULL) {
        printf("%d ",tmp->data);
        tmp = tmp->prev;
    }
    printf("\n");
}

