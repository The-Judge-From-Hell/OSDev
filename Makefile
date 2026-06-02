CC = x86_64-elf-gcc # C compiler in use for my system
AS = nasm # assembler used in this
LD = x86_64-elf-ld # target build

# compiler flags
CFLAGS = -ffreestanding -mcmodel=small -mno-red-zone -mno-mmx -mno-sse -c
# assembler flags
ASFLAGS = -f elf64

# find all C files in directory
C_SOURCES = $(wildcard *.c)

# yoink .c filenames to .o filenames, explicitly append interrupt.o
OBJS = $(C_SOURCES:.c=.o) interrupt.o

all: kernel.bin

# kernel.o forced first for boot execution
kernel.bin: kernel.o $(OBJS)
	$(LD) -T linker.ld -o kernel.bin kernel.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f *.o kernel.bin