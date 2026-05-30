typedef unsigned long long size_t; // C has no idea what the fuck 'size_t' actually is! it should be built in by this time.
// memset - used to overwrite a buffer with a single value.
void* memset (void *buffer_pointer, int value, size_t n){ // pointer, value, times to write. void* as it have to accept any kind of garbage.
    unsigned char *p = buffer_pointer;                    // this pos is crucial as C cant do shit on void!! use it to point and change it to char for actual action.
    for (size_t i = 0; i < n ; i++){                      // Ah! for loop! to iterate for n times to overwrite.
        p[i] = (unsigned char)value;                      // actual overwrite.
    }                                                     // used to clear terminal screens for example.
    return buffer_pointer;                                // return the final shit.
}
// memcopy - used to copy data from src to dest buffer without even comparing the length..
void* memcpy (void *destination, const void *source, size_t n){ // dest, src, times. again..
   unsigned char *d = destination;                               // dest pointer as char, src as const char as source should not be fucked.
   const unsigned char *s = source;
   for(size_t i = 0; i < n; i++){                                // copying...
       d[i] = s[i];
   }
   return destination;                                           // return the copied shit.
}
// memmove - same same. but different.
void* memmove (void *destination, const void *source, size_t n){ // dest, src, times. again.. same here.
   unsigned char *d = destination;                               // dest pointer as char, src as const char as source should not be fucked.
   const unsigned char *s = source;
   if (d < s){                                                  // Source head of destination. Copy forward.
       for (size_t i = 0; i < n; i++){
           d[i] = s[i];
       }
   }
   else if (d > s){                                             // Destination ahead of source. Copy backward from end.
       for (size_t i = n; i > 0; i--){                          // from n to 0. i-- vouches for that..
           d[i - 1] = s[i - 1];
       }
   }
   return destination;
}
// memcmp - compares if you are you.
int memcmp (const void *source, const void *copy, size_t byte_count){ // func def source, copy
    const unsigned char *s = source;                     // make pointers to move forward
    const unsigned char *c = copy;
    for (size_t i = 0; i < byte_count; i++){       // loop for byte_count times. and compare.
        if (s[i] != c[i]){
            return s[i] - c[i];                   // returns diff
        }
    }
    return 0;                                     // returns 0 if all same
}
// memchr - hunter and finder
void* memchr(const void *source, const int search, size_t size){ // source, search target, no of bytes to look..
    const unsigned char *s = source;                             // char to increment a byte at a time.
     for (size_t i = 0; i < size; i++){                          // classic for loop
        if (s[i] == search){                                     // condition for equality
            return (void*)&s[i];                                 // if equal, send memory address
        }
     }
     return 0;                                                   // returns 0 if not found in limit.
}