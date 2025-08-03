#include "arch/STM32F103/usb.h"
void usb0_init(void)
{
    /* PB12 input with push-up */
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_IOPBEN, 1);
    SET_REG_FIELD(GPIOB->CRH, GPIO_CRH_MODE12, MODE_INPUT);
    SET_REG_FIELD(GPIOB->CRH, GPIO_CRH_CNF12, CNF_INPUT_PUSH_PULL);
    GPIOB->ODR |= (1 << 12);

    USART1_init();
}

int usb0_available(void)
{
    return (GPIOB->IDR >> 12) & 1;
}