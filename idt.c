#include "idt.h"
#include "io.h"

// mem block for 256 manual pages..
struct idt_gate idt[256];
struct idt_register idtr;

// 0x08 is the standard index for Kernel Code in a 64-bit GDT
#define KERNEL_CS 0x08

// Declare the assembly as an external function
extern void isr33(void);
extern void exception_stub(void);

// func that cuts 64 bit addrs to fit the struct.
void set_idt_gates(uint8_t num, uint64_t base){
    idt[num].offset_low  = (base & 0xFFFF); // first 16 bits
    idt[num].offset_mid  = ((base >> 16) & 0xFFFF); // middle 16 bits
    idt[num].offset_high = ((base >> 32) & 0xFFFFFFFF); // last 32 bits

    //kernel exec properties
    idt[num].selector = KERNEL_CS; 
    idt[num].ist = 0;
    idt[num].types_attr = 0x8E; // current flag ring 0
    idt[num].zero = 0; // intel weight
}

// start the shit
void idt_starter(void){

    // 1. Map system exceptions (0-31) to rescue stub
    for (int i = 0; i < 32; i++){
        set_idt_gates(i, (uint64_t)exception_stub);
    }

    // 2. Map your keyboard (33)
    set_idt_gates(33, (uint64_t)isr33);

    // Remap PIC (Move IRQs away from CPU exceptions)
    outb(0x20, 0x11); // Master PIC Init
    outb(0xA0, 0x11); // Slave PIC Init
    outb(0x21, 0x20); // Master offset = 0x20 (Vector 32-39)
    outb(0xA1, 0x28); // Slave offset = 0x28
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01); // 8086 mode
    outb(0xA1, 0x01);

    // Unmask Keyboard line (IRQ 1) only, mask rest for safety
    outb(0x21, 0xFD); // 0xFD = 11111101b (IRQ 1 unmasked)
    outb(0xA1, 0xFF); // Disable all slave IRQs
    
    // config idtr tables
    idtr.limit = (sizeof(struct idt_gate) * 256) - 1;
    idtr.base = (uint64_t)&idt;

    // [FUTURE NOTE]: This is where we will map individual index numbers
    // to custom driver functions (e.g., set_idt_gates(33, (uint64_t)keyboard_handler);)
    // if you are reading this and its blank, you have fucked up somewhere...

    // push the shit to cpu's idtr reg
    __asm__ volatile ("lidt %0" : : "m"(idtr));
}