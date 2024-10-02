
// kernel.c
// Author: kesballoReal

#include <stdint.h>
#include "memory.h"

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

typedef struct {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
} multiboot_header_t;

// Header Multiboot
__attribute__((section(".multiboot")))
multiboot_header_t multiboot_header = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM,
    0,
    0,
    0,
    0,
    0,
};

// Video Memory things
#define VIDEO_MEMORY (char *)0xb8000
#define MAX_WIDTH 80
#define MAX_HEIGHT 25

// Cursors variables for printf
unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void update_cursor() {
    unsigned short position = cursor_y * MAX_WIDTH + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, position >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, position & 0xFF);
}

void put_char(char c) {
    char *vidptr = VIDEO_MEMORY + (cursor_y * MAX_WIDTH + cursor_x) * 2;
    *vidptr = c;
    *(vidptr + 1) = 0x07; // White on black color
    cursor_x++;
    
    if (cursor_x >= MAX_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_HEIGHT) {
        cursor_y = MAX_HEIGHT - 1;
    }

    update_cursor(); // Updates the cursor
}

// Funzione per stampare stringhe
void print_string(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
            if (cursor_y >= MAX_HEIGHT) {
                cursor_y = MAX_HEIGHT - 1;
            }
        } else {
            put_char(*str);
        }
        str++;
    }
}

// Do i need to explain this?
void kernel_main() {
    memory_init();  // Memory init

    cursor_x = 0;
    cursor_y = 0; 
    
    const char *msg = "Hello from cikappaOS Kernel!";
    print_string(msg);

    

    // Infinite loop for not stopping the kernel.
    while (1) {
    }
}
