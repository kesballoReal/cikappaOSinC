#include "video.h"

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
    char *vidptr = (char *)VIDEO_MEMORY + (cursor_y * MAX_WIDTH + cursor_x) * 2; 
    *vidptr = c;
    *(vidptr + 1) = 0x07;
    cursor_x++;
    
    if (cursor_x >= MAX_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_HEIGHT) {
        cursor_y = MAX_HEIGHT - 1; 
    }

    update_cursor(); 
}


void clear() {
    char *vidptr = (char *)VIDEO_MEMORY;
    
    for (int i = 0; i < MAX_WIDTH * MAX_HEIGHT; i++) {
        vidptr[i * 2] = ' ';      
        vidptr[i * 2 + 1] = 0x07;
    }

    cursor_x = 0; 
    cursor_y = 0;
    update_cursor(); 
}


void video_init() {
    unsigned int *videomem = (unsigned int *)VIDEO_MEMORY;
    for (int i = 0; i < MAX_WIDTH * MAX_HEIGHT; i++) {
        videomem[i] = 0x0F00; 
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}

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
