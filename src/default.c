#include "default.h"

#include <stdlib.h>

const struct mallocator MALLOCATOR_DEFAULT = {
    .alloc   = malloc,
    .realloc = realloc,
    .free    = free
};