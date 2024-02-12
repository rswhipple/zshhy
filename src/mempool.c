#include "../inc/mempool.h"

void initialize_pool(memory_pool_t* mempool) { 
    mempool->free_blocks = NULL;
    for (int i = 0; i < POOL_SIZE; i++) {
        block_t* new_block = (block_t*)mempool->pool[i];
        new_block->next = mempool->free_blocks;
        mempool->free_blocks = new_block;
    }
}

char* allocate(memory_pool_t* mempool) { 
    if (!mempool->free_blocks) return NULL;

    block_t* available_block = mempool->free_blocks;
    mempool->free_blocks = available_block->next;
    return (char*)available_block;
}

void deallocate(memory_pool_t* mempool, void* ptr) {
    block_t* returned_block = (block_t*)ptr;
    returned_block->next = mempool->free_blocks;
    mempool->free_blocks = returned_block;
}
