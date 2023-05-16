#ifndef FOMINMV_ALLOC_BASE_H
#define FOMINMV_ALLOC_BASE_H

#include <stddef.h>

typedef void *(*malloctor_alloc_t)(size_t);
typedef void *(*malloctor_realloc_t)(void *, size_t);
typedef void (*mallocator_free_t)(void *);

struct mallocator {
    malloctor_alloc_t   alloc;
    malloctor_realloc_t realloc;
    mallocator_free_t   free;
};

#endif