#include "kernel/defs.h"
#include "kernel/libc.h"

typedef struct block {
    size_t size;
    size_t prev_size;
    char mem[0];
} block_t;


extern unsigned long _heap_start, _heap_end;
block_t *first_block, *last_block;

#define PREV_INUSE(block) (((block_t *) (block))->prev_size & 1)
#define INUSE(block) (((block_t *) (block))->size & 1)

#define CLEAR_USE_BIT(size) ((size) & ~0x1)
#define SET_USE_BIT(block)                \
    do {                                  \
        ((block_t *) block)->size |= 0x1; \
    } while (0)

#define NEXT_BLOCK(block)            \
    ((block_t *) ((char *) (block) + \
                  CLEAR_USE_BIT(((block_t *) (block))->size)))
#define PREV_BLOCK(block)            \
    ((block_t *) ((char *) (block) - \
                  CLEAR_USE_BIT(((block_t *) (block))->prev_size)))

#define NEXT_INUSE(block) (INUSE(NEXT_BLOCK(block)))

void mm_init(void)
{
    first_block = (block_t *) &_heap_start;
    first_block->size = ALIGN_DOWN(&_heap_end - &_heap_start - sizeof(block_t));
    last_block = NEXT_BLOCK(first_block);
    last_block->size = 1;
    last_block->prev_size = first_block->size;
    first_block->prev_size = 1;
}

void *malloc(int size)
{
    block_t *found = 0;
    size = ALIGN_UP(size + sizeof(block_t));
    /* Programmers have the responsibility to ensure the memory blocks are not
     * corrupt for the security reason. */
    for (block_t *block = first_block; block < last_block;
         block = NEXT_BLOCK(block)) {
        if (INUSE(block))
            continue;
        if (CLEAR_USE_BIT(block->size) < size)
            continue;
        found = block;
        break;
    }

    if (!found)
        return 0;

    if (found->size < size + sizeof(block_t)) {
        SET_USE_BIT(found);
        NEXT_BLOCK(found)->prev_size |= 1;
        return found->mem;
    }

    block_t *next_block = (block_t *) ((char *) found + size);
    next_block->size = found->size - size;
    found->size = size | 1;
    next_block->prev_size = found->size;
    return found->mem;
}

static block_t *merge(block_t *l, block_t *r)
{
    l->size = CLEAR_USE_BIT(l->size) + CLEAR_USE_BIT(r->size);
    return l;
}

void free(void *addr)
{
    block_t *block = (block_t *) (addr - sizeof(block_t));
    block->size &= ~1;
    NEXT_BLOCK(block)->prev_size &= ~1;
    if (!PREV_INUSE(block))
        block = merge(PREV_BLOCK(block), block);
    if (!NEXT_INUSE(block))
        block = merge(block, NEXT_BLOCK(block));
}

void memset(void *addr, unsigned char c, int n)
{
    uint32_t x = c;
    x |= x << 8;
    x |= x << 16;
    while (n >= 4) {
        *(uint32_t *) addr = x;
        addr += 4;
        n -= 4;
    }
    while (n--) {
        *(unsigned char *) addr = c;
        addr++;
    }
}
