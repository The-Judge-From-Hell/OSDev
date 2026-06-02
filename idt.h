#ifndef IDT_H_
#define IDT_H_
#include <stdint.h>

// Exactly 16 bytes. Structural mapping for a single 64-bit IDT crisis page.
struct idt_gate{
    uint16_t offset_low;   // Bits 0..15 of handler function address. bcoz x86 has baggage
    uint16_t selector;     // tells which GDT segment to use (usually 0x08)
    uint8_t ist;           // Interrupt Stack Table used when double-fault and main was corrupted (keep 0 for now)
    uint8_t types_attr;    // safety and types. 7th=validity, 6-5th=r0 auth, 3-0th=modern 64bit interrupt gate.
    uint16_t offset_mid;   // Bits 16..31 of handler function address. added in middle as 32 bit addrs became mainstream
    uint32_t offset_high;  // Bits 32..63 of handler function address. added this extra as 64 bit addrs became mainstream.
    uint32_t zero;         // dead weight @ intel, completely 0 for padding purps..
} __attribute__((packed)); // so that compiler doesnt add extras

// actually, idt is stored in RAM, cpu dk abt it. so, a reg called IDTR points to it
// its picky about its 10 bytes. so 2 tell the size and 8 tell the address.
struct idt_register{
    uint16_t limit; // table size -1 so that cpu doesnt fuck off the limit
    uint64_t base;  // location og gates in ram.
} __attribute__((packed)); // same. no compiler extras

// Public functions other files can see
void idt_starter(void);
void set_idt_gates(uint8_t num, uint64_t base);

#endif