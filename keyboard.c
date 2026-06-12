#include "io.h"
#include "vga.h"
#include <stdint.h>

#define keyboard_port 0x60
#define pic_master_cmd 0x20

char commands[256];
uint8_t index = 0;

// Index = Scancode. Value = ASCII.
const unsigned char kbd_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '};

static const char kbd_us_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '};

static int shift_state = 0;
// process placeholder
void processor(char *text, uint8_t index)
{
    kprint("\n", VGA_COLOR_BLACK);
    kprint(text, VGA_COLOR_MAGENTA);
    kprint("\nOSZero > ", VGA_COLOR_LIGHT_GREEN);
    index = 0;
}
// avtual handling happend here
void keyboard_handler(void){
     uint8_t scaned = inb(keyboard_port);

     switch (scaned){
     case 0x2A:
     case 0x36:
         shift_state = 1;
         break; // Shift Press

     case 0xAA:
     case 0xB6:
         shift_state = 0;
         break; // Shift Release

     case 0x0E: // Backspace
         if (index > 0){
             index--;
             commands[index] = '\0';
             kprint("\b", VGA_COLOR_BLACK);
         }
         break;

     case 0x1C:
         if (index < 255){
             commands[index] = '\0';
         }
         processor(commands, index);
         index = 0;
         
         goto eoi;
         break;
     default:
         // Translate scan code -> ASCII based on shift_state
         break;
     }

    // keyboard sends signal when key is pressed and released
    // so, release shouldnt trigger the print cmds
    if (scaned & 0x80){
        goto eoi;
    }

    // actual scaned to ascii convs
    // checks if the shift is active. if yes, fucks off to the shift layout
    // if not, uses normal one.
    if (scaned < 128){
        // holy fuck. finally a ternary operator comes handy!!
        char letter = shift_state ? kbd_us_shift[scaned] : kbd_us[scaned];
        if (letter != 0){
            if (index < 255){
                commands[index] = letter;
                index++;
            }
            char str[2] = {letter, '\0'};
            kprint(str, 0x0F);
        }
    }

    // CRITICAL: Send "End of Interrupt" (EOI) signal back to the PIC.
    // If i don't do this, the PIC thinks the CPU is still busy and will
    // freeze all future keyboard signals forever.
    eoi:
        outb(pic_master_cmd, 0x20);
}