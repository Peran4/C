#pragma once
#include <stdio.h>

struct point_t {
    double x;
    double y;
};


int comparator(const void *ptr1, const void *ptr2);
int sort(void *arr, int N, size_t size, int (*func)(const void *ptr1, const void *ptr2));
int comp_int(const void *a, const void *b);
int comp_double(const void *a, const void *b);
int comp_point(const void *p1, const void *p2);
