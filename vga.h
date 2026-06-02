#ifndef VGA_H
#define VGA_H

// 1. The Color Palette Macros. made this for simpler usage.
#define VGA_COLOR_BLACK 0x0
#define VGA_COLOR_BLUE 0x1
#define VGA_COLOR_GREEN 0x2
#define VGA_COLOR_CYAN 0x3
#define VGA_COLOR_RED 0x4
#define VGA_COLOR_MAGENTA 0x5
#define VGA_COLOR_BROWN 0x6
#define VGA_COLOR_LIGHT_GREY 0x7
#define VGA_COLOR_DARK_GREY 0x8
#define VGA_COLOR_LIGHT_BLUE 0x9
#define VGA_COLOR_LIGHT_GREEN 0xA
#define VGA_COLOR_LIGHT_CYAN 0xB
#define VGA_COLOR_LIGHT_RED 0xC
#define VGA_COLOR_LIGHT_MAGENTA 0xD
#define VGA_COLOR_YELLOW 0xE
#define VGA_COLOR_WHITE 0xF

// 2. The Dynamic Attribute Combiner Macro. this shit combines some shit.
#define VGA_ATTRIBUTE(bg, fg) (((bg & 0x0F) << 4) | (fg & 0x0F))

// 3. Driver Function Declarations.
void wipe_display(unsigned char color_attr);
void kprint(const char *text, unsigned char color_attr);

// 4. Console width and height 
#define vga_width 80
#define vga_height 25
#define vga_buffer_size (vga_width * vga_height)
#endif