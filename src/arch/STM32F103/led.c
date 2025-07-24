#include "arch/STM32F103/led.h"

void debug_shine_led(void)
{
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC_CRH = 0x44144444;
    while (1) {
        GPIOC_ODR ^= (1ULL << 13);
        for (int c = 0; c < 50000; c++)
            ;
    }
}
