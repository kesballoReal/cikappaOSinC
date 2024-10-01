#include <stdint.h>
#include "memory.h"

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

// Struttura dell'header Multiboot
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

// Costante per l'inizio della memoria video
#define VIDEO_MEMORY (char *)0xb8000
#define MAX_WIDTH 80
#define MAX_HEIGHT 25

// Variabili globali per la posizione corrente del cursore
unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

// Funzione per scrivere su una porta I/O
void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Funzione per aggiornare la posizione del cursore
void update_cursor() {
    unsigned short position = cursor_y * MAX_WIDTH + cursor_x;
    outb(0x3D4, 14); // Porta per il registro di alto
    outb(0x3D5, position >> 8);
    outb(0x3D4, 15); // Porta per il registro di basso
    outb(0x3D5, position & 0xFF);
}

// Funzione per scrivere caratteri sulla memoria video
void put_char(char c) {
    char *vidptr = VIDEO_MEMORY + (cursor_y * MAX_WIDTH + cursor_x) * 2;
    *vidptr = c;       // Carattere
    *(vidptr + 1) = 0x07; // Colore (bianco su sfondo nero)
    cursor_x++;
    
    // Gestisci il cambio di riga
    if (cursor_x >= MAX_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_HEIGHT) {
        cursor_y = MAX_HEIGHT - 1; // Mantieni l'altezza
    }

    update_cursor(); // Aggiorna il cursore
}

// Funzione per stampare stringhe
void print_string(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
            if (cursor_y >= MAX_HEIGHT) {
                cursor_y = MAX_HEIGHT - 1; // Mantieni l'altezza
            }
        } else {
            put_char(*str);
        }
        str++;
    }
}


// Funzione principale del kernel
void kernel_main() {
    memory_init();  // Inizializza la memoria

    cursor_x = 0; // Resetta il cursore all'inizio
    cursor_y = 0; // Resetta il cursore all'inizio
    
    const char *msg = "Booting from cikappaOS.iso...";
    print_string(msg);

    

    // Loop infinito per mantenere il kernel in esecuzione
    while (1) {
    }
}
