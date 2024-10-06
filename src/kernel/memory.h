
// memory.h
// Author: kesballoReal

#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"
#include <stddef.h>

#define ONE_MB (1 * 1024 * 1024)  // One megabyte in bytes (1.048.576)
#define MEMORY_POOL_SIZE (ONE_MB * 64) // Limit of memory (64 MB)
#define MIN_BLOCK_SIZE 16


typedef struct block {
    struct block *next;
    uint32_t size;
} block_t;


void memory_init(void);
void* memory_alloc(uint32_t size);
void memory_free(void* ptr);

#endif // MEMORY_H
