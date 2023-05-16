#include "default.h"

#include <stdlib.h>

const struct mallocator_vtable MALLOCATOR_VTABLE_DEFAULT = {
    .alloc   = malloc,
    .realloc = realloc,
    .free    = free
};

const mallocator_t MALLOCATOR_DEFAULT = {
    .vtable = &MALLOCATOR_VTABLE_DEFAULT
};