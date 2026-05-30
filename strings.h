#ifndef strings_h_
#define strings_h_

typedef unsigned long long size_t; // C has no idea what the fuck 'size_t' actually is! it should be built in by this time.
int strlen (void *string);
char *strcpy(char *destination, const char *source);
int strcmp(const char *source, const char *copy);

#endif