#include "strings.h"

// this shit prints out strings to screen or clears it.
typedef unsigned long long size_t;

// learnt structs literally for this, idk where to use them anywhere else.
// but they are cool..
struct vga_out{
    unsigned char character;
    unsigned char attribute;
};


//yoinks the screen blank
void wipe_display(unsigned char color_attr){
    struct vga_out *screen = (struct vga_out *)0xB8000;

    for (size_t i = 0; i < 2000; i++){
        screen[i].character = ' ';
        screen[i].attribute = color_attr;
    }
}

// prints some shit by pushing it to buffer.
void kprint(const char *text, unsigned char color_attr){
    struct vga_out *screen = (struct vga_out *)0xB8000;
    for (size_t i = 0; text[i] != '\0'; i++){
        screen[i].character = text[i];
        screen[i].attribute = color_attr;
    }
}