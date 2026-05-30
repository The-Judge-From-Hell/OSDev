typedef unsigned long long size_t; // C has no idea what the fuck 'size_t' actually is! it should be built in by this time.

// strlen - counts the string length or whatever
int* strlen (void *string){
    const unsigned char *s = string;
    for (size_t i=0; ;i++){ // no check condition as it should be infinite
        if (s[i] == '\0'){  // not "" as "" is str and '' is chr
            return i;       // returns count.
        } 
    }
}

// strcpy - copies a string to other 
char* strcpy (char *destination, const char *source){
    unsigned char *d = destination;
    const unsigned char *s = source;
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

// strcmp - compare 2 strings for n bytes limit
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