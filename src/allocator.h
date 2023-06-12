#ifndef FOMINMV_ALLOCATOR_ALLOCATOR_H
#define FOMINMV_ALLOCATOR_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

struct AllocatorVTable;

typedef struct {
    const struct AllocatorVTable *vtable;
} Allocator;

typedef void *(*AllocatorAlloc)(Allocator *, size_t);
typedef void *(*AllocatorRealloc)(Allocator *, void *, size_t);
typedef void (*AllocatorFree)(Allocator *, void *);

struct AllocatorVTable {
    AllocatorAlloc   alloc;
    AllocatorRealloc realloc;
    AllocatorFree    free;
};

Allocator Allocator_mk(const struct AllocatorVTable *vtable);

const struct AllocatorVTable *Allocator_getVTable(const Allocator *allocator);

bool Allocator_canAll(const Allocator *allocator);

void *Allocator_alloc(Allocator *allocator, size_t size);

bool Allocator_canRealloc(const Allocator *allocator);

void *Allocator_reallocIfCan(Allocator *allocator, void *block, size_t newSize);

void *Allocator_realloc(Allocator *allocator, void *block, size_t newSize);

bool Allocator_canFree(const Allocator *allocator);

bool Allocator_freeIfCan(Allocator *allocator, void *block);

void Allocator_free(Allocator *allocator, void *block);

bool Allocator_isValid(const Allocator *allocator);

bool AllocatorVTable_isValid(const struct AllocatorVTable *vtable);

#endif