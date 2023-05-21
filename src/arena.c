#include "arena.h"

#include <assert.h>
#include <stdlib.h>

const struct mallocator_vtable MALLOCATOR_ARENA_VTABLE = {
    .alloc   = (mallocator_alloc_t) mallocator_arena_alloc,
    .realloc = NULL,
    .free    = NULL
};

mallocator_arena_t mallocator_arena_mk(void *block, size_t size) {
    assert(block);

    return (mallocator_arena_t) {
        .allocator = mallocator_mk(&MALLOCATOR_ARENA_VTABLE),
        .block     = block,
        .total     = size,
        .used      = 0
    };
}

mallocator_arena_t mallocator_arena_mk_alloc(mallocator_t *allocator, size_t size, bool *failed) {
    assert(mallocator_valid(alloca));

    void *block = mallocator_alloc(allocator, size);

    if (!block && failed)
        *failed = true;

    return (mallocator_arena_t) {
        .allocator = mallocator_mk(&MALLOCATOR_ARENA_VTABLE),
        .block     = block,
        .total     = size,
        .used      = 0
    };
}

mallocator_arena_t mallocator_arena_mk_malloc(size_t size, bool *failed) {
    void *block = malloc(size);

    if (!block && failed)
        *failed = true;

    return (mallocator_arena_t) {
        .allocator = mallocator_mk(&MALLOCATOR_ARENA_VTABLE),
        .block     = block,
        .total     = size,
        .used      = 0
    };
}

void mallocator_arena_free(mallocator_arena_t *allocator) {
    assert(mallocator_arena_valid(allocator));
    free(allocator->block);
}

void *mallocator_arena_block(const mallocator_arena_t *allocator) {
    assert(mallocator_arena_valid(allocator));
    return allocator->block;
}

size_t mallocator_arena_total(const mallocator_arena_t *allocator) {
    assert(mallocator_arena_valid(allocator));
    return allocator->total;
}

size_t mallocator_arena_used(const mallocator_arena_t *allocator) {
    assert(mallocator_arena_valid(allocator));
    return allocator->used;
}

void *mallocator_arena_alloc(mallocator_arena_t *allocator, size_t size) {
    assert(mallocator_arena_valid(allocator));

    if (allocator->used + size > allocator->total)
        return NULL;

    void *block = allocator->block + allocator->used;

    allocator->used += size;

    return block;
}

bool mallocator_arena_valid(const mallocator_arena_t *allocator) {
    return mallocator_valid((const mallocator_t *) allocator)
        && allocator->block
        && allocator->used <= allocator->total;
}