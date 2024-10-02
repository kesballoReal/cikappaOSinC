// kernel.c
// Author: kesballoReal

#include <stdint.h>
#include "memory.h"
#include "video.h"
#include "keyboard.h"

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

void kernel_main() {
    memory_init();  // Inizializzazione della memoria
    video_init();   // Inizializzazione della grafica
    
    print_string("Hello from cikappaOS Kernel!\n");
    
    char last_char = '\0'; // Variabile per tenere traccia dell'ultimo carattere stampato
    
    // Ciclo infinito per non fermare il kernel.
    while (1) {
        char c = input(); // Leggi un carattere dalla tastiera
        if (c != '\0' && c != last_char) {  // Stampa solo se il carattere è valido e diverso dall'ultimo
            put_char(c); // Mostra il carattere sullo schermo
            last_char = c; // Aggiorna l'ultimo carattere stampato
        }

        // Aggiungi un breve ritardo per evitare cicli troppo veloci
        for (volatile int i = 0; i < 100000; i++);
    }
}
