
// memory.c
// Author: kesballoReal

#include "memory.h"
#include "video.h"
#include "stdint.h"

static uint8_t memory_pool[MEMORY_POOL_SIZE];
static block_t* free_list = NULL; 

// Init this memory baby
void memory_init(void) {
    free_list = (block_t*)memory_pool;       
    free_list->next = NULL;             
    free_list->size = MEMORY_POOL_SIZE - sizeof(block_t);
}

void* memory_alloc(uint32_t size) {
    size = (size + 7) & ~7; 
    if (size < MIN_BLOCK_SIZE) {
        size = MIN_BLOCK_SIZE; 
    }

    block_t* current = free_list;
    block_t* previous = NULL;

    while (current) {
        if (current->size >= size) {
            if (current->size > size + sizeof(block_t)) {
                block_t* new_block = (block_t*)((uint8_t*)current + sizeof(block_t) + size);
                new_block->size = current->size - size - sizeof(block_t);
                new_block->next = current->next;
                current->next = new_block;
                current->size = size;
            }

            if (previous) {
                previous->next = current->next;
            } else {
                free_list = current->next;
            }
            return (uint8_t*)current + sizeof(block_t);
        }
        previous = current;
        current = current->next;
    }

    print_string("\nMemory allocation failed: Not enough memory!\n");
    return NULL;
}

// Do i REALLY need to explain this? Oh cmon..
void memory_free(void* ptr) {
    if (!ptr) return;

    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->next = free_list;
    free_list = block; 
}
