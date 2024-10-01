
// memory.h
// Author: kesballoReal

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define MEMORY_POOL_SIZE 102400 // Limit of memory (100 kilobytes)
#define MIN_BLOCK_SIZE 16

typedef struct block {
    struct block *next;
    uint32_t size;
} block_t;


void memory_init(void);
void* memory_alloc(uint32_t size);
void memory_free(void* ptr);

#endif // MEMORY_H
