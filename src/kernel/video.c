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
    char *vidptr = (char *)VIDEO_MEMORY + (cursor_y * MAX_WIDTH + cursor_x) * 2; // Casting dell'indirizzo
    *vidptr = c;
    *(vidptr + 1) = 0x07; // Colore bianco su sfondo nero
    cursor_x++;
    
    if (cursor_x >= MAX_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_HEIGHT) {
        cursor_y = MAX_HEIGHT - 1; // Limit to the bottom of the screen
    }

    update_cursor(); // Aggiorna il cursore
}

void video_init() {
    // Inizializza la memoria video a uno stato pulito
    unsigned int *videomem = (unsigned int *)VIDEO_MEMORY;
    for (int i = 0; i < MAX_WIDTH * MAX_HEIGHT; i++) {
        videomem[i] = 0x0F00; // Imposta il colore e pulisce la memoria
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(); // Aggiorna il cursore inizialmente
}

void print_string(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
            if (cursor_y >= MAX_HEIGHT) {
                cursor_y = MAX_HEIGHT - 1; // Limita al fondo dello schermo
            }
        } else {
            put_char(*str);
        }
        str++;
    }
}
