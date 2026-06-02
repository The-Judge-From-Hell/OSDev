#ifndef IO_H_
#define IO_H_

// reads things from hw port
static inline unsigned char inb(unsigned short port){
    unsigned char res;
    // runs x86 "in" command to read data to al register
    __asm__ volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
    return res;
}

// writes things to hw port
static inline void outb(unsigned short port, unsigned char data){
    // runs x86 "out" command to push some shit to mobo port from cpu
    __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

#endif