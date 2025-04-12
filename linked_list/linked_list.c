#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "linked_list.h"


struct linked_list_t* ll_create(void) {
    struct linked_list_t *tmp = malloc(sizeof(struct linked_list_t));
    if(tmp == NULL) {
        return NULL;
    }
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;
}

int ll_push_back(struct linked_list_t* ll, char *value) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL)) {
        return 1;
    }
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->data = malloc(sizeof(char) * (strlen(value)+1));
    if(tmp->data == NULL) {
        free(tmp);
        return 2;
    }
    strcpy(tmp->data,value);
    if(ll_is_empty(ll)) {
        tmp->next = NULL;
        ll->head = tmp;
        ll->tail = tmp;
        return 0;
    }
    ll->tail->next = tmp;
    tmp->next = NULL;
    ll->tail = tmp;
    return 0;
}

int ll_push_front(struct linked_list_t* ll, char *value) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL)) {
        return 1;
    }
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if(tmp == NULL) {
        return 2;
    }
    tmp->data = malloc(sizeof(char) * (strlen(value)+1));
    if(tmp->data == NULL) {
        free(tmp);
        return 2;
    }

    strcpy(tmp->data,value);
    if(ll_is_empty(ll)) {
        tmp->next = NULL;
        ll->head = tmp;
        ll->tail = tmp;
        return 0;
    }
    tmp->next = ll->head;
    ll->head = tmp;
    return 0;
}

int ll_size(const struct linked_list_t* ll) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL)) {
        return -1;
    }
    if(ll->tail == NULL && ll->head == NULL) {
        return 0;
    }
    struct node_t *tmp = ll->head;
    int i=1;
    while(tmp->next != NULL) {
        i++;
        tmp = tmp->next;
    }
    return i;
}

int ll_pop_front(struct linked_list_t* ll, int *err_code) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL) || ll->head == NULL) {
        if(err_code != NULL) {
            *err_code = 1;
        }
        return 0;
    }
    struct node_t *tmp = ll->head;
    ll->head = ll->head->next;
    if(ll->head == NULL) {
        ll->tail = NULL;
    }
    free(tmp->data);
    free(tmp);
    if(err_code != NULL) {
        *err_code = 0;
    }
    return 1;
}

int ll_is_empty(const struct linked_list_t* ll) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL)) {
        return -1;
    }
    if(ll->tail == NULL && ll->head == NULL) {
        return 1;
    }
    return 0;
}


void ll_clear(struct linked_list_t* ll) {
    if(ll == NULL || ll->head == NULL || ll->tail == NULL) {
        return;
    }
    while(!ll_is_empty(ll)) {
        ll_pop_front(ll,NULL);
    }
}

void ll_display(const struct linked_list_t* ll) {
    if(ll == NULL || ll->head == NULL || ll->tail == NULL) {
        return;
    }
    struct node_t *tmp = ll->head;
    while(tmp != NULL) {
        printf("%s ",tmp->data);
        tmp = tmp->next;
    }
}

int ll_is_sorted_ascending(const struct linked_list_t* ll) {
    if(ll == NULL || ll->head == NULL || ll->tail == NULL) {
        return -1;
    }
    int len = ll_size(ll);
    struct node_t *tmp = ll->head;
    for(int i=0; i<len-1; i++) {
        if(strcmp(tmp->data,tmp->next->data) > 0) {
            return 0;
        }
        tmp = tmp->next;

    }
    return 1;
}

int ll_insert_words(struct linked_list_t* ll, int N, ...) {
    if(ll == NULL || (ll->tail == NULL && ll->head != NULL) || (ll->head == NULL && ll->tail != NULL) || N <= 0) {
        return -1;
    }
    if(!ll_is_sorted_ascending(ll)) {
        return -1;
    }
    va_list ap;
    va_start(ap,N);
    int i=0;
    for(; i<N; i++) {
        char *str = va_arg(ap,char *);
        struct node_t *tmp = malloc(sizeof(struct node_t));
        if(tmp == NULL) {
            return i;
        }
        tmp->data = malloc(sizeof(char) * (strlen(str)+1));
        if(tmp->data == NULL) {
            free(tmp);
            return i;
        }
        strcpy(tmp->data,str);
        struct node_t *aft = ll->head;
        struct node_t *bef = NULL;
        while(aft != NULL) {
            if(strcmp(tmp->data,aft->data) < 0) {
                break;
            }
            bef = aft;
            aft = aft->next;
        }
        if(bef == NULL) {
            ll->head = tmp;
        }
        else {
            bef->next = tmp;
        }
        if(aft == NULL) {
            ll->tail = tmp;
        }
        tmp->next = aft;
    }
    return i;
}

