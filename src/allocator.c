#include "allocator.h"

#include <assert.h>
#include <string.h>

Allocator Allocator_mk(const struct AllocatorVTable *vtable) {
    assert(AllocatorVTable_isValid(vtable));
    return (Allocator) { vtable };
}

const struct AllocatorVTable *Allocator_getVTable(const Allocator *allocator) {
    assert(Allocator_isValid(allocator));
    return allocator->vtable;
}

bool Allocator_canAll(const Allocator *allocator) {
    assert(Allocator_isValid(allocator));

    const struct AllocatorVTable *vtable = allocator->vtable;

    return vtable->realloc
        && vtable->free;
}

void *Allocator_alloc(Allocator *allocator, size_t size) {
    assert(Allocator_isValid(allocator));
    return allocator->vtable->alloc(allocator, size);
}

bool Allocator_canRealloc(const Allocator *allocator) {
    assert(Allocator_isValid(allocator));
    return allocator->vtable->realloc;
}

void *Allocator_reallocIfCan(Allocator *allocator, void *block, size_t newSize) {
    return Allocator_canRealloc(allocator) ? Allocator_realloc(allocator, block, newSize)
                                           : NULL;
}

void *Allocator_realloc(Allocator *allocator, void *block, size_t newSize) {
    assert(Allocator_isValid(allocator) && allocator->vtable->realloc);
    return allocator->vtable->realloc(allocator, block, newSize);
}

bool Allocator_canFree(const Allocator *allocator) {
    assert(Allocator_isValid(allocator));
    return allocator->vtable->free;
}

bool Allocator_freeIfCan(Allocator *allocator, void *block) {
    if (Allocator_canFree(allocator)) {
        Allocator_free(allocator, block);
        return true;
    }

    return false;
}

void Allocator_free(Allocator *allocator, void *block) {
    assert(Allocator_isValid(allocator) && allocator->vtable->free);
    allocator->vtable->free(allocator, block);
}

bool Allocator_isValid(const Allocator *allocator) {
    return allocator
        && AllocatorVTable_isValid(allocator->vtable);
}

bool AllocatorVTable_isValid(const struct AllocatorVTable *vtable) {
    return vtable
        && vtable->alloc;
}