#ifndef FOMINMV_ALLOCATOR_STD_H
#define FOMINMV_ALLOCATOR_STD_H

#include "allocator.h"

extern const struct AllocatorVTable Allocator_STD_VTABLE;
extern const Allocator              Allocator_STD_INSTANCE;

extern const struct AllocatorVTable Allocator_STD_FORCE_VTABLE;
extern const Allocator              Allocator_STD_FORCE_INSTANCE;

#endif