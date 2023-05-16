#include "force.h"

#include <stdio.h>
#include <stdlib.h>

static void malloc_failed_(size_t size);

const struct mallocator_vtable MALLOCATOR_VTABLE_FORCE = {
    .alloc   = mallocator_force_alloc,
    .realloc = mallocator_force_realloc,
    .free    = mallocator_force_free
};

const mallocator_t MALLOCATOR_FORCE = {
    .vtable = &MALLOCATOR_VTABLE_FORCE
};

void *mallocator_force_alloc(mallocator_t *allocator, size_t size) {
    void *block = malloc(size);

    if (!block)
        malloc_failed_(size);

    return block;
}

void *mallocator_force_realloc(mallocator_t *allocator, void *block, size_t new_size) {
    void *new_block = realloc(block, new_size);

    if (!new_block)
        malloc_failed_(new_size);

    return new_block;
}

void malloc_failed_(size_t size) {
    fprintf(
        stderr,
        "Failed to allocate block of %zd bytes",
        size
    );

    exit(EXIT_FAILURE);
}

void mallocator_force_free(mallocator_t *allocator, void *block) {
    free(block);
}