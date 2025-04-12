#include "heap.h"
#define MAX_HEAP 67108864

struct heap_manager_t heap_manager;

size_t size_to_sizechunk(size_t size) {
    return size + sizeof(struct memory_chunk_t) + 8;
}

size_t sizechunk_to_size(size_t size_chunk) {
    return size_chunk - sizeof(struct memory_chunk_t) - 8;
}

int8_t *chunk_end(struct memory_chunk_t *mem_chunk) {
    return (int8_t *)mem_chunk + size_to_sizechunk(mem_chunk->size);
}

void calc_sum_control(struct memory_chunk_t *mem_chunk) {
    int8_t *ptr = (int8_t *)mem_chunk;

    mem_chunk->control_sum = 0;
    for(int8_t i=0; i<16; i++) {
        mem_chunk->control_sum += *(ptr + i);
    }

    mem_chunk->control_sum += mem_chunk->size;
}

int heap_setup(void) {
    heap_manager.memory_start = custom_sbrk(0);
    if(heap_manager.memory_start == NULL) {
        return -1;
    }
    heap_manager.first_memory_chunk = NULL;
    heap_manager.memory_size = 0;
    return 0;
}

void heap_clean(void) {
    heap_manager.memory_start  = NULL;
    custom_sbrk(-heap_manager.memory_size);
    heap_manager.first_memory_chunk = NULL;
    heap_manager.memory_size = 0;
}

int8_t check_control_sum(struct memory_chunk_t *mem_chunk) {
    int8_t *ptr = (int8_t *)mem_chunk;
    size_t sum=0;
    for(int i=0; i<16; i++) {
        sum += *(ptr+i);
    }
    sum += mem_chunk->size;
    if(sum != mem_chunk->control_sum) {
        return 1;
    }
    return 0;
}

int heap_validate(void) {
    if(heap_manager.memory_start == NULL) {
        return 2;
    }

    struct memory_chunk_t *mem_chunk = heap_manager.first_memory_chunk;
    while(mem_chunk != NULL) {
        if(check_control_sum(mem_chunk)) {
            return 3;
        }

        for(int i = 0; i < 4; i++) {
            if(*((int8_t *)mem_chunk + sizeof(struct memory_chunk_t) + i) != '%' || *((int8_t *)mem_chunk + size_to_sizechunk(mem_chunk->size) - 4 + i) != '%') {
                return 1;
            }
        }

        mem_chunk = mem_chunk->next;
    }
    return 0;
}

void insert_fances(struct memory_chunk_t *mem_chunk) {
    for(int8_t i=0; i<4; i++) {
        *((int8_t *)mem_chunk + sizeof(struct memory_chunk_t) + i) = '%';
        *((int8_t *)mem_chunk + size_to_sizechunk(mem_chunk->size) - 4 + i) = '%';
    }
}

void* heap_malloc(size_t size) {
    if(heap_manager.memory_start == NULL || heap_validate() || size == 0) {
        return NULL;
    }

    size_t allocated_memory = 0;
    struct memory_chunk_t *prev = NULL, *cur_chunk = heap_manager.first_memory_chunk;
    struct memory_chunk_t *allocating_chunk = NULL;

    if(cur_chunk != NULL && (int8_t *)cur_chunk != (int8_t *)heap_manager.memory_start) {
        if((int8_t *)cur_chunk - (int8_t *)heap_manager.memory_start >= (long)size_to_sizechunk(size)) {
            allocating_chunk = (struct memory_chunk_t *)heap_manager.memory_start;
            heap_manager.first_memory_chunk = allocating_chunk;
            allocating_chunk->next = cur_chunk;
            cur_chunk->prev = allocating_chunk;
            calc_sum_control(cur_chunk);
            allocating_chunk->prev = NULL;
            allocating_chunk->size = size;
            calc_sum_control(allocating_chunk);

            insert_fances(allocating_chunk);

            return (int8_t *)allocating_chunk + sizeof(struct memory_chunk_t) + 4;
        }
    }

    while(1) {
        if(cur_chunk == NULL) {
            allocating_chunk = cur_chunk;
            break;
        }

        if(prev != NULL && (int8_t *)cur_chunk - chunk_end(prev) >= (long)size_to_sizechunk(size)) {
            allocating_chunk = (struct memory_chunk_t *)chunk_end(prev);
            break;
        }

        allocated_memory += size_to_sizechunk(cur_chunk->size);
        prev = cur_chunk;
        cur_chunk = cur_chunk->next;
    }


    if(allocated_memory + size_to_sizechunk(size) >= heap_manager.memory_size) {}

    if(heap_manager.memory_size + size_to_sizechunk(size) > MAX_HEAP || custom_sbrk(size_to_sizechunk(size)) == NULL) {
        return NULL;
    }
    heap_manager.memory_size += size_to_sizechunk(size);

    if(cur_chunk == NULL) {
        if(heap_manager.first_memory_chunk == NULL) {
            allocating_chunk = (struct memory_chunk_t *)heap_manager.memory_start;
            heap_manager.first_memory_chunk = allocating_chunk;
            allocating_chunk->next = NULL;
            allocating_chunk->prev = NULL;
            allocating_chunk->size = size;
            calc_sum_control(allocating_chunk);
        }
        else {
            allocating_chunk = (struct memory_chunk_t *)chunk_end(prev);
            prev->next = allocating_chunk;
            allocating_chunk->prev = prev;
            calc_sum_control(prev);
            allocating_chunk->next = NULL;
            allocating_chunk->size = size;
            calc_sum_control(allocating_chunk);
        }
    }
    else {
        allocating_chunk = (struct memory_chunk_t *)chunk_end(prev);
        prev->next = allocating_chunk;
        allocating_chunk->prev = prev;
        cur_chunk->prev = allocating_chunk;
        allocating_chunk->next = cur_chunk;
        allocating_chunk->size = size;
        calc_sum_control(prev);
        calc_sum_control(cur_chunk);
        calc_sum_control(allocating_chunk);
    }

    insert_fances(allocating_chunk);

    return (int8_t *)allocating_chunk + sizeof(struct memory_chunk_t) + 4;
}

void* heap_calloc(size_t number, size_t size) {
    int8_t *mem_chunk = heap_malloc(number * size);

    if(mem_chunk == NULL) {
        return NULL;
    }

    for(size_t i=0; i<number*size; i++) {
        mem_chunk[i] = '\0';
    }
    return mem_chunk;
}

enum pointer_type_t get_pointer_type(const void* const pointer) {
    if(pointer == NULL) {
        return pointer_null;
    }

    if(heap_manager.first_memory_chunk == NULL) {
        return pointer_unallocated;
    }

    if(heap_validate()) {
        return pointer_heap_corrupted;
    }

    int8_t *ptr = (int8_t *)pointer;

    struct memory_chunk_t *cur_chunk = heap_manager.first_memory_chunk;
    while(cur_chunk != NULL) {
        if((int8_t *)cur_chunk + sizeof(struct memory_chunk_t) + 4 == ptr) {
            return pointer_valid;
        }

        if(ptr >= (int8_t *)cur_chunk && ptr < (int8_t *)cur_chunk + sizeof(struct memory_chunk_t)) {
            return pointer_control_block;
        }

        if((ptr >= (int8_t *)cur_chunk + sizeof(struct memory_chunk_t) && ptr < (int8_t *)cur_chunk + sizeof(struct memory_chunk_t) + 4) || (ptr >= chunk_end(cur_chunk) - 4 && ptr < chunk_end(cur_chunk))) {
            return pointer_inside_fences;
        }

        if(ptr > (int8_t *)cur_chunk + sizeof(struct memory_chunk_t) + 4 && ptr < chunk_end(cur_chunk) - 4) {
            return pointer_inside_data_block;
        }
        cur_chunk = cur_chunk->next;
    }
    return pointer_unallocated;
}

void heap_free(void* memblock) {
    if(get_pointer_type(memblock) != pointer_valid) {
        return;
    }

    int8_t *ptr = (int8_t *)memblock;
    ptr -= sizeof(struct memory_chunk_t) + 4;

    struct memory_chunk_t *mem_chunk = (struct memory_chunk_t *)ptr;
    struct memory_chunk_t *prev = mem_chunk->prev, *next = mem_chunk->next;

    if(prev == NULL && next == NULL) {
        heap_manager.first_memory_chunk = NULL;
        return;
    }

    if(prev != NULL) {
        prev->next = next;
        calc_sum_control(prev);
    }

    if(next != NULL) {
        if(mem_chunk == heap_manager.first_memory_chunk) {
            heap_manager.first_memory_chunk = next;
        }
        next->prev = prev;
        calc_sum_control(next);
    }
}

void* heap_realloc(void* memblock, size_t count) {
    if(heap_validate() || size_to_sizechunk(count) + heap_manager.memory_size > MAX_HEAP) {
        return NULL;
    }

    if(memblock == NULL) {
        return heap_malloc(count);
    }

    if(get_pointer_type(memblock) != pointer_valid) {
        return NULL;
    }

    if(!count) {
        heap_free(memblock);
        return NULL;
    }

    int8_t *ptr = (int8_t *)memblock;
    ptr -= sizeof(struct memory_chunk_t) + 4;

    struct memory_chunk_t *old = (struct memory_chunk_t *)ptr;
    if(old->size == count) {
        return memblock;
    }
    size_t old_size = old->size;

    heap_free(memblock);

    void *ptr_new_data = heap_malloc(count);
    if(ptr_new_data != NULL) {
        if(old_size > count) {
            memcpy(ptr_new_data,memblock,count);
        }
        else {
            memcpy(ptr_new_data,memblock,old_size);
        }
    }

    return ptr_new_data;
}

size_t heap_get_largest_used_block_size(void) {
    if(heap_validate() || heap_manager.memory_size == 0) {
        return 0;
    }

    struct memory_chunk_t *mem_chunk = heap_manager.first_memory_chunk;
    size_t largest = 0;
    while(mem_chunk != NULL) {
        if(mem_chunk->size > largest) {
            largest = mem_chunk->size;
        }
        mem_chunk = mem_chunk->next;
    }
    return largest;
}
