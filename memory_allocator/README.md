I implemented custom memory allocators with fences and validation functions:
malloc → heap_malloc,
calloc → heap_calloc,
realloc → heap_realloc.
The files custom_unistd.h and memmanager.c are not mine.
