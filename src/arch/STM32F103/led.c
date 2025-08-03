#include "arch/STM32F103/led.h"

void debug_shine_led(void)
{
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_IOPCEN, 1);
    SET_REG_FIELD(GPIOC->CRH, GPIO_CRH_MODE13, MODE_OUTPUT_10MHz);
    SET_REG_FIELD(GPIOC->CRH, GPIO_CRH_CNF13, CNF_OUTPUT_GP_PUSH_PULL);
    while (1) {
        GPIOC->ODR ^= (1ULL << 13);
        for (int c = 0; c < 500000; c++)
            ;
    }
}
