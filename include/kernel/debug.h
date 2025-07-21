#include "kernel/regs.h"

#define PANIC()            \
    do {                   \
        debug_shine_led(); \
    } while (0)

static void debug_shine_led(void)
{
    RCC_APB2ENR = RCC_APB2ENR_IOPCEN;
    GPIOC_CRH = 0x44144444;
    while (1) {
        GPIOC_ODR ^= (1ULL << 13);
        for (int c = 0; c < 50000; c++)
            ;
    }
}
