#include "force.h"

#include <stdio.h>
#include <stdlib.h>

static void malloc_failed_(size_t size);

const struct mallocator MALLOCATOR_FORCE = {
    .alloc   = mforce_alloc,
    .realloc = mforce_realloc,
    .free    = mforce_free
};

void *mforce_alloc(size_t size) {
    void *block = malloc(size);

    if (!block)
        malloc_failed_(size);

    return block;
}

void *mforce_realloc(void *block, size_t new_size) {
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

void mforce_free(void *block) {
    free(block);
}