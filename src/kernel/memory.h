#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_POOL_SIZE 102400 // Dimensione totale della memoria
#define MIN_BLOCK_SIZE 16      // Dimensione minima del blocco

typedef struct block {
    struct block *next; // Puntatore al blocco successivo
    uint32_t size;      // Dimensione del blocco
} block_t;

// Funzioni di gestione della memoria
void memory_init(void);
void* memory_alloc(uint32_t size);
void memory_free(void* ptr);

#endif // MEMORY_H
