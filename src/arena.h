#ifndef FOMINMV_ALLOCATOR_ARENA_H
#define FOMINMV_ALLOCATOR_ARENA_H

#include <stdbool.h>
#include <stddef.h>

#include "allocator.h"

typedef struct {
    mallocator_t  allocator;
    mallocator_t *parent;
    void         *block;
    size_t        total;
    size_t        used;
} mallocator_arena_t;

extern const struct mallocator_vtable MALLOCATOR_ARENA_VTABLE;

mallocator_arena_t mallocator_arena_mk(void *block, size_t size);
mallocator_arena_t mallocator_arena_mk_alloc(mallocator_t *allocator, size_t size, bool *failed);
void mallocator_arena_free(mallocator_arena_t *allocator);
mallocator_t *mallocator_arena_parent(const mallocator_arena_t *allocator);
void *mallocator_arena_block(const mallocator_arena_t *allocator);
size_t mallocator_arena_total(const mallocator_arena_t *allocator);
size_t mallocator_arena_used(const mallocator_arena_t *allocator);
void *mallocator_arena_alloc(mallocator_arena_t *allocator, size_t size);
bool mallocator_arena_valid(const mallocator_arena_t *allocator);

#endif