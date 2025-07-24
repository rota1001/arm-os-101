#include "kernel/defs.h"
#include "kernel/usart.h"

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_arg __builtin_va_arg

#define IS_ERROR(ptr) (((unsigned long) ptr) & 0x3)
#define PTR2ERR(ptr) ((unsigned long) ptr)
#define ERR2PTR(err) ((void *) err)

void putchar(int x);

long getchar(void);

void printf(const char *fmt, ...);

void getline(char *s, int len);

void mm_init(void);

/* Notice that `mem_init` has to be called before any memory allocation */
void *malloc(int size);

/* Notice that `addr` has to be ensured to be a valid address */
void free(void *addr);
