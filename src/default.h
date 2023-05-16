#ifndef FOMINMV_ALLOCATOR_DEFAULT_H
#define FOMINMV_ALLOCATOR_DEFAULT_H

#include "allocator.h"

extern const struct mallocator_vtable MALLOCATOR_VTABLE_DEFAULT;
extern const mallocator_t             MALLOCATOR_DEFAULT;

void *mallocator_default_alloc(mallocator_t *allocator, size_t size);
void *mallocator_default_realloc(mallocator_t *allocator, void *block, size_t new_size);
void mallocator_default_free(mallocator_t *allocator, void *block);

#endif