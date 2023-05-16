#ifndef FOMINMV_ALLOCATOR_FORCE_H
#define FOMINMV_ALLOCATOR_FORCE_H

#include <stddef.h>

#include "allocator.h"

extern const struct mallocator_vtable MALLOCATOR_VTABLE_FORCE;
extern const mallocator_t             MALLOCATOR_FORCE;

void *mallocator_force_alloc(mallocator_t *allocator, size_t size);
void *mallocator_force_realloc(mallocator_t *allocator, void *block, size_t new_size);
void mallocator_force_free(mallocator_t *allocator, void *block);

#endif
