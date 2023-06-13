#include "arena.h"

#include <assert.h>
#include <stdlib.h>

const struct AllocatorVTable ArenaAllocator_VTABLE = {
    .alloc   = (AllocatorAlloc) ArenaAllocator_alloc,
    .realloc = NULL,
    .free    = NULL
};

ArenaAllocator ArenaAllocator_FromBlock(void *block, size_t size) {
    assert(block);

    return (ArenaAllocator) {
        .allocator = Allocator_mk(&ArenaAllocator_VTABLE),
        .parent    = NULL,
        .block     = block,
        .total     = size,
        .used      = 0
    };
}

ArenaAllocator ArenaAllocator_Alloc(Allocator *allocator, size_t size, bool *failed) {
    void *block = Allocator_alloc(allocator, size);

    if (!block && failed)
        *failed = true;

    return (ArenaAllocator) {
        .allocator = Allocator_mk(&ArenaAllocator_VTABLE),
        .parent    = allocator,
        .block     = block,
        .total     = size,
        .used      = 0
    };
}

void ArenaAllocator_freeBlock(ArenaAllocator *allocator) {
    Allocator *parent = AreanAllocator_getParent(allocator);

    if (parent)
        Allocator_freeIfCan(parent, allocator->block);
}

Allocator *AreanAllocator_getParent(const ArenaAllocator *allocator) {
    assert(AreanAllocator_isValid(allocator));
    return allocator->parent;
}

void *ArenaAllocator_getBlock(const ArenaAllocator *allocator) {
    assert(AreanAllocator_isValid(allocator));
    return allocator->block;
}

size_t ArenaAllocator_getTotal(const ArenaAllocator *allocator) {
    assert(AreanAllocator_isValid(allocator));
    return allocator->total;
}

size_t ArenaAllocator_getUsed(const ArenaAllocator *allocator) {
    assert(AreanAllocator_isValid(allocator));
    return allocator->used;
}

void *ArenaAllocator_alloc(ArenaAllocator *allocator, size_t size) {
    assert(AreanAllocator_isValid(allocator));

    size_t newUsed = allocator->used + size;

    if (newUsed > allocator->total)
        return NULL;

    void *block = allocator->block + allocator->used;

    allocator->used = newUsed;

    return block;
}

void ArenaAllocator_freeAll(ArenaAllocator *allocator) {
    assert(AreanAllocator_isValid(allocator));
    allocator->used = 0;
}

bool AreanAllocator_isValid(const ArenaAllocator *allocator) {
    return Allocator_isValid((const Allocator *) allocator)
        && (!allocator->parent || Allocator_isValid(allocator->parent))
        && allocator->block
        && allocator->used <= allocator->total;
}