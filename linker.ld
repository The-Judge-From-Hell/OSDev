/* ==========================================
   STAGE 3: THE LINKER SCRIPT (link.ld)
   ========================================== */

ENTRY(_start)

SECTIONS
/* Tells the linker where to physically arrange our code blocks */
{
    /* GRUB expects the kernel to be loaded at exactly 1 Megabyte in RAM */
    . = 1M;

    /* Executable Code Section */
    .text : ALIGN(4K)
    {
        *(.multiboot)   /* CRITICAL: The GRUB passport stamp MUST go first */
        *(.text)        /* All your compiled assembly and C functions */
    }

    /* Read-Only Data (Constant strings like "Hello World") */
    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Initialized Global Variables */
    .data : ALIGN(4K)
    {
        *(.data)
    }

    /* Uninitialized Data & Your 16KB Hardware Stack */
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}