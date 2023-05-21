#ifndef FOMINMV_ALLOCATOR_ALLOCATOR_H
#define FOMINMV_ALLOCATOR_ALLOCATOR_H

#include <stdbool.h>
#include <stddef.h>

struct mallocator_vtable;

typedef struct {
    const struct mallocator_vtable *vtable;
} mallocator_t;

typedef void *(*mallocator_alloc_t)(mallocator_t *, size_t);
typedef void *(*mallocator_realloc_t)(mallocator_t *, void *, size_t);
typedef void (*mallocator_free_t)(mallocator_t *, void *);

struct mallocator_vtable {
    mallocator_alloc_t   alloc;
    mallocator_realloc_t realloc;
    mallocator_free_t    free;
};

mallocator_t mallocator_mk(const struct mallocator_vtable *vtable);
const struct mallocator_vtable *mallocator_vtable(const mallocator_t *allocator);
bool mallocator_full(const mallocator_t *allocator);
void *mallocator_alloc(mallocator_t *allocator, size_t size);
bool mallocator_can_realloc(const mallocator_t *allocator);
void *mallocator_safe_realloc(mallocator_t *allocator, void *block, size_t new_size);
void *mallocator_realloc(mallocator_t *allocator, void *block, size_t new_size);
bool mallocator_can_free(const mallocator_t *allocator);
bool mallocator_safe_free(mallocator_t *allocator, void *block);
void mallocator_free(mallocator_t *allocator, void *block);
bool mallocator_valid(const mallocator_t *allocator);
bool mallocator_vtable_valid(const struct mallocator_vtable *vtable);

#endif