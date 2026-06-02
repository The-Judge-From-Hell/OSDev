#include "io.h"
#include "vga.h"

#define keyboard_port 0x60
#define pic_master_cmd 0x20

// Index = Scancode. Value = ASCII.
const unsigned char kbd_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '};


// avtual handling happend here
void keyboard_handler(void){
    unsigned char scaned = inb(keyboard_port);

    // keyboard sends signal when key is pressed and released
    // so, release shouldnt trigger the print cmds
    if (scaned & 0x80){
        goto eoi;
    }

    // actual scaned to ascii convs
    if (scaned < 128 && kbd_us[scaned] != 0){ // if less than 128 and in uskbd,
        char letter = kbd_us[scaned]; // assigns letter
        char str[2] = {letter, '\0'}; // Print single char string
        kprint(str, 0x0F);            // fucks off to screen.
    }

    // Clear the screen or print a confirmation to verify life

    // For now, we will just print to prove the hardware pipeline works
    // (Assuming you have an absolute basic print character debug or kprint available)
    // kprint("\nIt actually works", 0xF);

    // 3. CRITICAL: Send "End of Interrupt" (EOI) signal back to the PIC.
    // If you don't do this, the PIC thinks the CPU is still busy and will
    // freeze all future keyboard signals forever.
    eoi:
        outb(pic_master_cmd, 0x20);
}