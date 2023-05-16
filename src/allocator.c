#include "allocator.h"

#include <assert.h>
#include <string.h>

mallocator_t mallocator_mk(const struct mallocator_vtable *vtable) {
    assert(mallocator_vtable_valid(vtable));
    return (mallocator_t) { vtable };
}

const struct mallocator_vtable *mallocator_vtable(const mallocator_t *allocator) {
    assert(mallocator_valid(allocator));
    return allocator->vtable;
}

void *mallocator_alloc(const mallocator_t *allocator, size_t size) {
    assert(mallocator_valid(allocator));
    return allocator->vtable->alloc(size);
}

void *mallocator_realloc(const mallocator_t *allocator, void *block, size_t new_size) {
    assert(mallocator_valid(allocator));
    return allocator->vtable->realloc(block, new_size);
}

void mallocator_free(const mallocator_t *allocator, void *block) {
    assert(mallocator_valid(allocator));
    allocator->vtable->free(block);
}

bool mallocator_valid(const mallocator_t *allocator) {
    return allocator
        && mallocator_vtable_valid(allocator->vtable);
}

bool mallocator_vtable_valid(const struct mallocator_vtable *vtable) {
    return vtable
        && vtable->alloc
        && vtable->realloc
        && vtable->free;
}