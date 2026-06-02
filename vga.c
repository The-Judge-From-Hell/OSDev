#include "strings.h"
#include "vga.h"

// this shit prints out strings to screen or clears it.
typedef unsigned long long size_t;

// learnt structs literally for this, idk where to use them anywhere else.
// but they are cool..
struct vga_out{
    unsigned char character;
    unsigned char attribute;
};

// put the pointer to hw address
volatile struct vga_out *screen = (volatile struct vga_out *)0xB8000;
unsigned int cursor_index = 0;

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

        // Print character using struct indexing
        else{
            screen[cursor_index].character = text[i];
            screen[cursor_index].attribute = color_attr;
            cursor_index++;
        }

        // Boundary check
        if (cursor_index >= vga_buffer_size){
            vga_scroll(color_attr);
        }
    }
}
// We pass the buffer in so the function doesn't use unsafe random pointers
void digitizer(int target_num, char *buffer){
    int count = 0;
    int neg_check = 0;

    // check for -ve numbers..
    if (target_num < 0){
        neg_check = 1;
        target_num = -target_num;
    }

    // if the number is literally 0
    if (target_num == 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    while (target_num != 0){
        // Add '0' to convert the raw math remainder into a printable text character
        buffer[count] = (target_num % 10) + '0';
        target_num = target_num / 10;
        count++;
    }
    // Add - to the end if needed (it gets reversed to the front)
    if (neg_check){
        buffer[count] = '-';
        count++;
    }

    // adding \0 so that string actually ends
    buffer[count] = '\0';

    // reverse the string
    int start = 0;
    int end = count - 1;
    while (start < end){
        // simple temporary variable swap
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}