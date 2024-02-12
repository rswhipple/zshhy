#ifndef _MEMPOOL_H
#define _MEMPOOL_H

#include "header.h"
#include <stdio.h>
#include <stdbool.h>

// macros
#define POOL_SIZE 10
#define BLOCK_SIZE 512

// structs
typedef struct block {
    struct block* next;
} block_t;

typedef struct {
    block_t* free_blocks;
    char pool[POOL_SIZE][BLOCK_SIZE];
} memory_pool_t;

// function prototypes
void initialize_pool(memory_pool_t* mempool);
char* allocate(memory_pool_t* mempool);
void deallocate(memory_pool_t* mempool, void* ptr);

#endif
