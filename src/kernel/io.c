#include <stdint.h>
#include "arch.h"
#include "kernel/libc.h"

#define clz __builtin_clz

void putchar(int x)
{
    if (x == '\n')
        USART1_putchar('\r');
    USART1_putchar(x);
}

long getchar(void)
{
    return USART1_getchar();
}

static void print_uint(unsigned int x)
{
    char tmp[10];
    int i = 0;
    tmp[0] = '0';
    while (x) {
        tmp[i++] = x % 10 + '0';
        x /= 10;
    }
    while (i >= 0)
        putchar(tmp[i--]);
}

void printf(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);
    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            putchar(*fmt);
            continue;
        }
        fmt++;
        switch (*fmt) {
        case '\0':
            goto DONE;
        case 's':
            const char *s = va_arg(vargs, const char *);
            while (*s)
                putchar(*s++);
            break;
        case 'c':
            putchar(*fmt);
            break;
        case 'd':
            int x = va_arg(vargs, int);
            int i = 0;
            if (x < 0) {
                putchar('-');
                x = -x;
            }
            print_uint(x);
            break;
        case 'u':
            unsigned int y = va_arg(vargs, unsigned int);
            print_uint(y);
            break;
        case 'x':
            unsigned int z = va_arg(vargs, unsigned int);
            for (int i = 7; i >= 0; i--) {
                putchar("0123456789abcdef"[(z >> (i << 2)) & 0xf]);
            }
            break;
        }
    }
DONE:
    va_end(vargs);
}

void getline(char *s, int len)
{
    char c;
    len--;
    while (((c = getchar()) != '\r') && (len--))
        *s++ = c;
    *s = 0;
}
