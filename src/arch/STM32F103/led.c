#include "arch/STM32F103/led.h"

void debug_shine_led(void)
{
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_IOPCEN, 1);
    GPIOC->CR.CNF13 = CNF_OUTPUT_GP_PUSH_PULL;
    GPIOC->CR.MODE13 = MODE_OUTPUT_10MHz;
    while (1) {
        GPIOC->ODR ^= (1ULL << 13);
        for (int c = 0; c < 500000; c++)
            ;
    }
}
