// declare so that compliler know that this shit already exists.
#include "vga.h"
#include "idt.h"

void wipe_display (unsigned char color_attr);
void kprint (const char *text, unsigned char color_attr);
extern void exception_stub(void);

void kernel_main (void){
    unsigned char color = VGA_ATTRIBUTE(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREEN);

    // Clear the screen to blue so tht i know this works and try print stuff
    wipe_display(color);
    kprint("Hello World! Booted finally. BTW, Welcome to OSZero!\n", color);
    
    // Initialize IDT setup
    idt_starter();

    // Clear interrupt flag (Unlock CPU input)
    __asm__ volatile("sti");
    
    // Core Executive Loop to keep the CPU alive
    while (1)
    {
        // Optional: Inline assembly to safely halt the CPU until next interrupt
        // and i dk some actual shit about asm.
        // i asked gemma and it wrote this.
        __asm__ __volatile__("hlt");
    }

}
void exception_handler(void){
    wipe_display(0x4F); // Bright Red Screen
    kprint("CRITICAL CPU EXCEPTION TRIGGERED! System Halted.", 0x4F);
    while (1){
        __asm__ volatile("hlt");
    }
}