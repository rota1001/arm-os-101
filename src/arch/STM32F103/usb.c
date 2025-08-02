#include "arch/STM32F103/usb.h"
void usb0_init(void)
{
    /* PB12 input with push-up */
    RCC->APB2ENR.IOPBEN = 1;
    GPIOB->CR.MODE12 = MODE_INPUT;
    GPIOB->CR.CNF12 = CNF_INPUT_PUSH_PULL;
    GPIOB->ODR |= (1 << 12);

    USART1_init();
}

int usb0_available(void)
{
    return (GPIOB->IDR >> 12) & 1;
}