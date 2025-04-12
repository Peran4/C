#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

struct heap_manager_t {
    void *memory_start;
    size_t memory_size;
    struct memory_chunk_t *first_memory_chunk;
};

extern struct heap_manager_t heap_manager;

struct __attribute__((packed)) memory_chunk_t {
    struct memory_chunk_t* prev;
    struct memory_chunk_t* next;
    size_t size;
    size_t control_sum;
};

enum pointer_type_t {
    pointer_null,
    pointer_heap_corrupted,
    pointer_control_block,
    pointer_inside_fences,
    pointer_inside_data_block,
    pointer_unallocated,
    pointer_valid
};


int heap_setup(void);
int heap_validate(void);
void heap_clean(void);
void* heap_malloc(size_t size);
void* heap_calloc(size_t number, size_t size);
void* heap_realloc(void* memblock, size_t new_size);
void  heap_free(void* memblock);
enum pointer_type_t get_pointer_type(const void* const pointer);
size_t heap_get_largest_used_block_size(void);


#endif //HEAP_H
