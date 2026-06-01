; i really dont know what the fuck this actually does.
; just followed the documentation and asked Gemma about this,

section .multiboot          ; multiboot header for GRUB
    align 4                 ; aligned for 4 bytes for GRUB
    dd 0x1BADB002           ; idk wtf is this. found it somewhere in docs
    dd 0x00                 ; initial but or smoeother fuck
    dd -(0x1BADB002 + 0x00) ; some checksum GRUB needs. idk why.

section .bss                ; to setup some stack for C
    align 16                ; idk why but 16..
    stack_bottom: resb 16384; reverse stack as x86 for some fucking reason grows down
    stack_top:              ; this shows upper limit or something.

section .text               ; Executable Machine Instructions
    global _start           ; flashes entry point to some linker
    extern kernel_main      ; says that C func is existing somewhere else

_start:
    mov esp, stack_top      ; CPU dk the stack location. this tells that.
    call kernel_main        ; fucks off to C kernel

.halt:
    hlt                     ; CPU sleeps if C ever returns
    jmp .halt               ; trap CPU here so that it doesnt fuckoff somewhere.