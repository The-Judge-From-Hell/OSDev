#include "idt.h"

// mem block for 256 manual pages..
struct idt_gate idt[256];
struct idt_register idtr;

// 0x08 is the standard index for Kernel Code in a 64-bit GDT
#define KERNEL_CS 0x08

// Declare the assembly as an external function
extern void isr33(void);

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
    // config idtr tables
    idtr.limit = (sizeof(struct idt_gate) * 256) - 1;
    idtr.base = (uint64_t)&idt;

    // [FUTURE NOTE]: This is where we will map individual index numbers
    // to custom driver functions (e.g., idt_set_gate(33, (uint64_t)keyboard_handler);)
    // if you are reading this and its blank, you have fucked up somewhere...

    // push the shit to cpu's idtr reg
    __asm__ volatile ("lidt %0" : : "m"(idtr));
}