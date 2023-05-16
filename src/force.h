#ifndef FOMINMV_ALLOC_FORCE_H
#define FOMINMV_ALLOC_FORCE_H

#include <stddef.h>

#include "types.h"

extern const struct mallocator MALLOCATOR_FORCE;

void *mforce_alloc(size_t size);
void *mforce_realloc(void *block, size_t new_size);
void mforce_free(void *block);

#endif
