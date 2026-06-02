[bits 64]
global isr33 ;interrupt service routine for keyboard
extern keyboard_handler ; some outside shit will link here

section .text

; The entry point the IDT will point to
isr33:
    ; 1. Save all volatile registers
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push rbp

    ; 2. Align Stack to 16 bytes safely
    mov rbp, rsp        ; rbp stores copy of original stack layout
    and rsp, -16        ; Clears lower 4 bits. Forces 16-byte alignment.

    ; 3. Jump to C (Safe now)
    call keyboard_handler

    ; 4. Restore original unaligned stack
    mov rsp, rbp

    ; 5. Restore registers
    pop rbp
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax

    ; Hardware return
    iretq

global exception_stub
extern exception_handler

exception_stub:
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    
    mov rbp, rsp
    and rsp, -16
    
    call exception_handler ; Call diagnostic C code
    
    mov rsp, rbp
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax
    iretq