[bits 64]
global isr33 ;interrupt service routine for keyboard
extern keyboard_handler ; some outside shit will link here

section .text

; The entry point the IDT will point to
isr33:
    push rbp
    mov rbp, rsp

    ; Save all volatile CPU registers so C code doesn't corrupt them
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11

    ; Jump into c's keyboard handler
    call keyboard_handler

    ; Restore all saved regs
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax

    pop rbp
    ; The critical hardware return instruction for 64-bit interrupts
    iretq