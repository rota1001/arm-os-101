#include "arch/STM32F103/usb.h"
void usb0_init(void)
{
    /* PB12 input with push-up */
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB_CRH &= ~(0xF << 16);
    GPIOB_CRH |= GPIO_CONF(GPIO_CNF_INPUT_PUSH_PULL, GPIO_MODE_INPUT) << 16;
    GPIOB_ODR |= (1 << 12);

    USART1_init();
}

int usb0_available(void)
{
    return (GPIOB_IDR >> 12) & 1;
}