#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"

int main() {
    int c;
    printf("Enter data type: ");
    if(!scanf("%d", &c)) {
        printf("Incorrect input");
        return 1;
    }
    int size;
    printf("Enter array size: ");
    if(!scanf("%d",&size)) {
        printf("Incorrect input");
        return 1;
    }
    if(size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    if(c == 0) {
        int *arr = malloc(sizeof(int) * size);
        if(arr == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter ints: ");
        for(int i=0; i<size; i++) {
            if(!scanf("%d", (arr+i))) {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
//            while(getchar() != '\n');
        }
        sort(arr,size,sizeof(int),comp_int);
        for(int i=0; i<size; i++) {
            printf("%d ", *(arr+i));
        }
        free(arr);
        return 0;
    }
    if(c == 1) {
        double *arr = malloc(sizeof(double) * size);
        if(arr == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter doubles: ");
        for(int i=0; i<size; i++) {
            if(!scanf("%lf", (arr+i))) {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
//            while(getchar() != '\n');
        }
        sort(arr,size,sizeof(double),comp_double);
        for(int i=0; i<size; i++) {
            printf("%lf ", *(arr+i));
        }
        free(arr);
        return 0;
    }
    if(c == 2) {
        struct point_t *arr = malloc(sizeof(struct point_t) * size);
        if(arr == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter points: ");
        for(int i=0; i<size; i++) {
            if(scanf("%lf %lf", &(arr+i)->x, &(arr+i)->y) != 2) {
                printf("Incorrect input");
                free(arr);
                return 1;
            }
            while(getchar() != '\n');
        }
        sort(arr,size,sizeof(struct point_t),comp_point);
        for(int i=0; i<size; i++) {
            printf("%lf %lf\n", (arr+i)->x,(arr+i)->y);
        }
        free(arr);
        return 0;
    }
    printf("Incorrect input data");
    return 2;
}


