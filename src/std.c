#include "std.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void *Allocator_stdAlloc_(Allocator *allocator, size_t size);
static void *Allocator_stdRealloc_(Allocator *allocator, void *block, size_t newSize);
static void Allocator_stdFree_(Allocator *allocator, void *block);

static void *Allocator_stdForceAlloc_(Allocator *allocator, size_t size);
static void *Allocator_stdForceRealloc_(Allocator *allocator, void *block, size_t newSize);

static void mallocFailed_(size_t size);

const struct AllocatorVTable Allocator_STD_VTABLE = {
    .alloc   = Allocator_stdAlloc_,
    .realloc = Allocator_stdRealloc_,
    .free    = Allocator_stdFree_ 
};

const Allocator Allocator_STD_INSTANCE = {
    .vtable = &Allocator_STD_VTABLE
};

const struct AllocatorVTable Allocator_STD_FORCE_VTABLE = {
    .alloc   = Allocator_stdForceAlloc_,
    .realloc = Allocator_stdForceRealloc_,
    .free    = Allocator_stdFree_ 
};

const Allocator Allocator_STD_FORCE_INSTANCE = {
    .vtable = &Allocator_STD_FORCE_VTABLE
};

void *Allocator_stdAlloc_(Allocator *allocator, size_t size) {
    assert(Allocator_isValid(allocator));
    return malloc(size);
}

void *Allocator_stdRealloc_(Allocator *allocator, void *block, size_t newSize) {
    assert(Allocator_isValid(allocator));
    return realloc(block, newSize);
}

void Allocator_stdFree_(Allocator *allocator, void *block) {
    assert(Allocator_isValid(allocator));
    return free(block);
}

void *Allocator_stdForceAlloc_(Allocator *allocator, size_t size) {
    assert(Allocator_isValid(allocator));

    void *block = malloc(size);

    if (!block)
        mallocFailed_(size);

    return block;
}

void *Allocator_stdForceRealloc_(Allocator *allocator, void *block, size_t newSize) {
    assert(Allocator_isValid(allocator));

    void *newBlock = realloc(block, newSize);

    if (!newBlock)
        mallocFailed_(newSize);

    return newBlock;
}

void mallocFailed_(size_t size) {
    fprintf(
        stderr,
        "Failed to allocate block of %zd bytes",
        size
    );

    exit(EXIT_FAILURE);
}