#include <stdint.h>
#include "arch.h"

#define ALIGN 4
#define ALIGN_DOWN(size) ((size) & ~(ALIGN - 1))
#define ALIGN_UP(size) ALIGN_DOWN((size) + (ALIGN - 1))

#define size_t uint32_t
