#ifndef FOMINMV_ALLOC_ALLOCATOR_H
#define FOMINMV_ALLOC_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef void *(*malloctor_alloc_t)(size_t);
typedef void *(*malloctor_realloc_t)(void *, size_t);
typedef void (*mallocator_free_t)(void *);

struct mallocator_vtable {
    malloctor_alloc_t   alloc;
    malloctor_realloc_t realloc;
    mallocator_free_t   free;
};

typedef struct {
    const struct mallocator_vtable *vtable;
} mallocator_t;

mallocator_t mallocator_mk(const struct mallocator_vtable *vtable);
const struct mallocator_vtable *mallocator_vtable(const mallocator_t *allocator);
void *mallocator_alloc(const mallocator_t *allocator, size_t size);
void *mallocator_realloc(const mallocator_t *allocator, void *block, size_t new_size);
void mallocator_free(const mallocator_t *allocator, void *block);
bool mallocator_valid(const mallocator_t *allocator);
bool mallocator_vtable_valid(const struct mallocator_vtable *vtable);

#endif