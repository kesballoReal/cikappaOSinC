#include "memory.h"

static uint8_t memory_pool[MEMORY_POOL_SIZE]; // Pool di memoria
static block_t* free_list = NULL;              // Lista dei blocchi liberi

// Inizializza la memoria
void memory_init(void) {
    free_list = (block_t*)memory_pool;         // Inizializza il primo blocco
    free_list->next = NULL;                    // Nessun blocco libero inizialmente
    free_list->size = MEMORY_POOL_SIZE - sizeof(block_t); // Imposta la dimensione
}

// Funzione per allocare memoria
void* memory_alloc(uint32_t size) {
    // Allinea la dimensione richiesta
    size = (size + 7) & ~7; // Allinea a 8 byte
    if (size < MIN_BLOCK_SIZE) {
        size = MIN_BLOCK_SIZE; // Usa la dimensione minima
    }

    block_t* current = free_list;
    block_t* previous = NULL;

    // Cerca un blocco libero che soddisfi la richiesta
    while (current) {
        if (current->size >= size) {
            // Trova un blocco adeguato
            if (current->size > size + sizeof(block_t)) {
                // Se il blocco è più grande del necessario, crea un nuovo blocco
                block_t* new_block = (block_t*)((uint8_t*)current + sizeof(block_t) + size);
                new_block->size = current->size - size - sizeof(block_t);
                new_block->next = current->next;
                current->next = new_block;
                current->size = size; // Riduci la dimensione del blocco attuale
            }

            // Rimuovi il blocco dalla lista dei blocchi liberi
            if (previous) {
                previous->next = current->next;
            } else {
                free_list = current->next; // Aggiorna la testa della lista
            }

            return (uint8_t*)current + sizeof(block_t); // Restituisce un puntatore all'area allocata
        }
        previous = current;
        current = current->next;
    }

    return NULL; // Memoria insufficiente
}

// Funzione per liberare memoria
void memory_free(void* ptr) {
    if (!ptr) return;

    // Ottieni l'intestazione del blocco
    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->next = free_list; // Aggiungi il blocco alla lista libera
    free_list = block; // Aggiorna la testa della lista
}
