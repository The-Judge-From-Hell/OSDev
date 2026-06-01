#include "strings.h"

// strlen - counts the string length or whatever
int strlen (void *string){
    const unsigned char *s = string;
    for (size_t i=0; ;i++){ // no check condition as it should be infinite
        if (s[i] == '\0'){  // not "" as "" is str and '' is chr
            return i;       // returns count.
        } 
    }
}

// strcpy - copies a string to other but i think its similar to memcpy but diff 
// datatype.
char* strcpy (char *destination, const char *source){
    char *d = destination; // make gcc happy
    const char *s = source; // make gcc happy
    for (size_t i = 0; ;i++){
        if (s[i] != '\0'){
            d[i] = s[i];
        }
        else {
            d[i] = '\0';
            return destination;
        }
    }
}

// strcmp - compare 2 strings for n bytes limit and same as memcmp but why??
int strcmp (const char *source, const char *copy){
    const unsigned char *s = source;
    const unsigned char *c = copy;
    for (size_t i = 0; ; i++){
        if (s[i] != c[i]){
            return s[i] - c[i];
        }
        if (s[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}