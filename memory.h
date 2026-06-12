#ifndef memory_h_
#define memory_h_

#include "types.h"
// this is a so called header file, which has defs of funcs created in other c files
// id relaay fucking know how they link to the c thing.
// i never mentioned "memory.c" in here nut included "memory.h" in in that c file

void *memset(void *buffer_pointer, int value, size_t n);
void *memcpy(void *destination, const void *source, size_t n);
void *memmove(void *destination, const void *source, size_t n);
int memcmp(const void *source, const void *copy, size_t byte_count);
void *memchr(const void *source, const int search, size_t size);

#endif