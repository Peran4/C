#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators.h"

int swap(void* ptr1, void* ptr2, size_t size) {
    void *tmp = malloc(size);
    if(tmp == NULL) {
        return 1;
    }
    memcpy(tmp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, tmp, size);
    free(tmp);
    return 0;
}

int sort(void *arr, int N, size_t size, int (*func)(const void *ptr1, const void *ptr2)) {
    if(arr == NULL || N <= 0 || size <= 0 || (*func) == NULL) {
        return 1;
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N-i-1; j++) {
            if((*func)(((char *)arr+(j*size)),((char *)arr+(j+1)*size)) > 0) {
                if(swap(((char *)arr+(j*size)),((char *)arr+(j+1)*size), size)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int comp_int(const void *a, const void *b) {
    if(a == NULL || b == NULL) {
        return 0;
    }
    if(*(int *)a > *(int *)b)
        return 1;
    if(*(int *)a == *(int *)b)
        return 0;
    return -1;
}

int comp_double(const void *a, const void *b) {
    if(a == NULL || b == NULL) {
        return 0;
    }
    if(*(double *)a > *(double *)b)
        return 1;
    if(*(double *)a == *(double *)b)
        return 0;
    return -1;
}

int comp_point(const void *p1, const void *p2) {
    if(p1 == NULL || p2 == NULL) {
        return 0;
    }
    if(((struct point_t *)p1)->x == ((struct point_t *)p2)->x) {
        if(((struct point_t *)p1)->y > ((struct point_t *)p2)->y)
            return 1;
        if(((struct point_t *)p1)->y == ((struct point_t *)p2)->y)
            return 0;
        return -1;
    }
    if(((struct point_t *)p1)->x > ((struct point_t *)p2)->x)
        return 1;
    if(((struct point_t *)p1)->x == ((struct point_t *)p2)->x)
        return 0;
    return -1;
}



