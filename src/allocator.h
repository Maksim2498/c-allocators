#ifndef FOMINMV_ALLOC_ALLOCATOR_H
#define FOMINMV_ALLOC_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef void *(*malloctor_alloc_t)(size_t);
typedef void *(*malloctor_realloc_t)(void *, size_t);
typedef void (*mallocator_free_t)(void *);

struct mallocator {
    malloctor_alloc_t   alloc;
    malloctor_realloc_t realloc;
    mallocator_free_t   free;
};

void *mallocator_alloc(const struct mallocator *allocator, size_t size);
void *mallocator_realloc(const struct mallocator *allocator, void *block, size_t new_size);
void mallocator_free(const struct mallocator *allocator, void *block);
bool mallocator_valid(const struct mallocator *allocator);

#endif