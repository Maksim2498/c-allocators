#ifndef FOMINMV_ALLOCATOR_ARENA_H
#define FOMINMV_ALLOCATOR_ARENA_H

#include <stdbool.h>
#include <stddef.h>

#include "allocator.h"

typedef struct {
    Allocator  allocator;
    Allocator *parent;
    void      *block;
    size_t     total;
    size_t     used;
} ArenaAllocator;

extern const struct AllocatorVTable ArenaAllocator_VTABLE;

ArenaAllocator ArenaAllocator_FromBlock(void *block, size_t size);

ArenaAllocator ArenaAllocator_Alloc(Allocator *allocator, size_t size, bool *failed);

void ArenaAllocator_freeBlock(ArenaAllocator *allocator);

Allocator *AreanAllocator_getParent(const ArenaAllocator *allocator);

void *ArenaAllocator_getBlock(const ArenaAllocator *allocator);

size_t ArenaAllocator_getTotal(const ArenaAllocator *allocator);

size_t ArenaAllocator_getUsed(const ArenaAllocator *allocator);

void *ArenaAllocator_alloc(ArenaAllocator *allocator, size_t size);

void ArenaAllocator_freeAll(ArenaAllocator *allocator);

bool AreanAllocator_isValid(const ArenaAllocator *allocator);

#endif