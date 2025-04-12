#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main(int argc, char **argv) {
    struct linked_list_t *ll = ll_create();
    if(ll == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    if(argc < 2) {
        printf("Not enough arguments");
        ll_clear(ll);
        free(ll);
        return 9;
    }
    for(int i=1; i<argc; i++) {
        int ret = ll_insert_words(ll,1,*(argv+i));
        if(ret < 1) {
            ll_clear(ll);
            free(ll);
            printf("Failed to allocate memory");
            return 8;
        }
    }
    ll_display(ll);
    ll_clear(ll);
    free(ll);
    return 0;
}