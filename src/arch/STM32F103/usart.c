#include "arch/STM32F103/usart.h"

void USART1_init(void)
{
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_AFIOEN, 1);
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_IOPAEN, 1);
    SET_REG_FIELD(RCC->APB2ENR, RCC_APB2ENR_USART1EN, 1);
    GPIOA->CR.MODE9 = MODE_OUTPUT_50MHz;
    GPIOA->CR.CNF9 = CNF_OUTPUT_AF_PUSH_PULL;
    GPIOA->CR.MODE10 = MODE_INPUT;
    GPIOA->CR.CNF10 = CNF_INPUT_ANALOG;

    USART1->BRR = 0x341; /* baud rate is 9600 (for fCK = 8MHz)*/

    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

/**
 * TODO: Non-blocking IO
 */
void USART1_putchar(int c)
{
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = c;
}

long USART1_getchar(void)
{
    while (!(USART1->SR & USART_SR_RXNE))
        ;
    long c = USART1->DR;
    ;
    return c;
}