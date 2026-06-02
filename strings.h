#ifndef strings_h_
#define strings_h_

// same shit here happening too. but the shit idk i get it.
typedef unsigned long long size_t; // C has no idea what the fuck 'size_t' actually is! it should be built in by this time.
int strlen (void *string);
char *strcpy(char *destination, const char *source);
int strcmp(const char *source, const char *copy);
char *itoa(long long value, char *str, int base); // for int to ascii.
char *itoah(unsigned long long value, char *str); // Specific for 64-bit Hex addresses

#endif