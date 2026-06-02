; i really dont know what the fuck this actually does.
; just followed the documentation and asked Gemma about this,

section .multiboot          ; multiboot header for GRUB
    align 4                 ; aligned for 4 bytes for GRUB
    dd 0x1BADB002           ; idk wtf is this. found it somewhere in docs
    dd 0x00                 ; initial but or smoeother fuck
    dd -(0x1BADB002 + 0x00) ; some checksum GRUB needs. idk why.

section .bss                ; to setup some stack for C
    align 4096              ; idk why but 4096..
    page_table_l4: resb 4096; Level 4 Page Map Table
    page_table_l3: resb 4096; Directory Pointer Table
    page_table_l2: resb 4096; Page Directory Table
    stack_bottom: resb 16384; reverse stack as x86 for some fucking reason grows down
    stack_top:              ; this shows upper limit or something.

section .rodata
    align 8
    gdt64:                  ; 64-Bit Global Descriptor Table
        dq 0                ; Null descriptor
    .code: equ $ - gdt64
        dq (1<<43) | (1<<44) | (1<<47) | (1<<53) ; 64-bit Code segment
    .pointer:
        dw $ - gdt64 - 1
        dq gdt64

section .text               ; Executable Machine Instructions
    bits 32                 ; I really dont know what it is, but it matters..
    global _start           ; flashes entry point to some linker
    extern kernel_main      ; says that C func is existing somewhere else

_start:
    mov esp, stack_top      ; CPU dk the stack location. this tells that.
    
    ; i really dont know any of this shit, but gemma told me to do so
    ; Identity map the first 2MB of RAM into the Page Tables
    mov eax, page_table_l3
    or eax, 0b11                ; Present + Writable flags
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b11
    mov [page_table_l3], eax

    mov eax, 0b10000011         ; Present + Writable + Huge Page (2MB)
    mov [page_table_l2], eax

    ; Point CPU to the Level 4 Page Table
    mov eax, page_table_l4
    mov cr3, eax

    ; Enable PAE (Physical Address Extension)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Switch EFER MSR into Long Mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable Paging to ignite Long Mode
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; Load 64-bit GDT and long-jump directly into 64-bit instructions
    lgdt [gdt64.pointer]
    jmp gdt64.code:_start64

bits 64
_start64:
    mov rsp, stack_top      ; Update stack pointer to 64-bit register
    call kernel_main        ; fucks off to your 64-bit C kernel

.halt:
    hlt                     ; CPU sleeps if C ever returns
    jmp .halt               ; trap CPU here so that it doesnt fuckoff somewhere.