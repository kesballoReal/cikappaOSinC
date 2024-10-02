// keyboard.c
// Author: kesballoReal

#include "keyboard.h"
#include <stdint.h>

#define KEYBOARD_PORT 0x60

// Funzione per leggere un byte da una porta I/O
static inline unsigned char inb(uint16_t port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Funzione per leggere il codice di scansione dalla tastiera
char read_keyboard() {
    unsigned char scancode = inb(KEYBOARD_PORT);
    
    // Gestire il rilascio dei tasti
    if (scancode & 0x80) {
        // Ignora i codici di rilascio
        return '\0';
    }
    
    // Mappatura dei codici di scansione in caratteri
    switch (scancode) {
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';
        case 0x39: return ' ';
        
        default: return '\0'; // Ritorna null se il codice di scansione non è mappato
    }
}

// Funzione input per ottenere un carattere dalla tastiera
char input() {
    char c;
    do {
        c = read_keyboard(); // Leggi un carattere dalla tastiera
    } while (c == '\0'); // Ignora i codici di rilascio

    return c; // Ritorna il carattere letto
}
