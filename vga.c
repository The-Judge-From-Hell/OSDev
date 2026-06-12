#include "strings.h"
#include "vga.h"
#include "io.h"
#include "types.h"
#include <stdint.h>

// learnt structs literally for this, idk where to use them anywhere else.
// but they are cool..
struct vga_out{
    unsigned char character;
    unsigned char attribute;
};

// put the pointer to hw address
volatile struct vga_out *screen = (volatile struct vga_out *)0xB8000;
unsigned int cursor_index = 0;
// cursor updater
void update_cursor(int x, int y){
    // since the screen is a buffer, i need to calc the cursor position from the last char
    // row, col pos. row x 80 gives totla lines above the char and + char gives char pos in the
    // cur line
    uint16_t offset = (x * 80) + y;

    //since crtc has 2 bytes, high and low,
    uint8_t high = (offset >> 8) & 0xFF;
    uint8_t low = offset & 0xFF;

    //writing to regs.
    outb(0x3D4, 14);
    outb(0x3D5, high);

    outb(0x3D4, 15);
    outb(0x3D5, low);
}

// scrolling mech
void vga_scroll(unsigned char color){
    
    // Moves rows 1-24 up into rows 0-23
    for (size_t i = 0; i < vga_width * (vga_height - 1); i++){
        screen[i] = screen[i + vga_width]; // Deep copies both char and attribute
    }
    
    // Clear the newly emptied bottom row
    size_t bottom_row_start = vga_width * (vga_height - 1); // moves to last row.
    for (size_t i = bottom_row_start; i < vga_buffer_size; i++){
        screen[i].character = ' ';
        screen[i].attribute = color;
    }
    
    // Keep the cursor locked to the start of the bottom row
    cursor_index = bottom_row_start;
}

//yoinks the screen blank
void wipe_display(unsigned char color_attr){
    for (size_t i = 0; i < vga_buffer_size; i++){
        screen[i].character = ' ';
        screen[i].attribute = color_attr;
    }
    cursor_index = 0;
}

// prints some shit by pushing it to buffer.
void kprint(const char *text, unsigned char color_attr){
    for (size_t i = 0; text[i] != '\0'; i++){ // works if not end of line

        // Newline pushes to next line
        if (text[i] == '\n'){
            // takes current index, divides by 80, adds 1, multiplys by 80
            cursor_index = ((cursor_index / vga_width) + 1) * vga_width;
        }

        // backspace mechanish
        else if (text[i] == '\b'){
            if (cursor_index > 0){ // so that a backspace dont fuck up my OS
                cursor_index--;
                screen[cursor_index].character = ' ';
                screen[cursor_index].attribute = color_attr;
            }
        }

        // Print character using struct indexing
        else{
            screen[cursor_index].character = text[i];
            screen[cursor_index].attribute = color_attr;
            cursor_index++;
        }
        int row = cursor_index / vga_width;
        int col = cursor_index % vga_width;
        update_cursor(row, col);
        // Boundary check
        if (cursor_index >= vga_buffer_size){
            vga_scroll(color_attr);
            row = cursor_index / vga_width;
            col = cursor_index % vga_width;
            update_cursor(row, col);
        }
    }
}
