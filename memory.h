#ifndef memory_h_
#define memory_h_

typedef unsigned long long size_t; // C has no idea what the fuck 'size_t' actually is! it should be built in by this time.

void *memset(void *buffer_pointer, int value, size_t n);
void *memcpy(void *destination, const void *source, size_t n);
void *memmove(void *destination, const void *source, size_t n);
int memcmp(const void *source, const void *copy, size_t byte_count);
void *memchr(const void *source, const int search, size_t size);

#endif