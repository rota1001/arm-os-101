#include "kernel/usart.h"

void USART1_init(void)
{
    RCC_APB2ENR |=
        RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    GPIOA_CRH &= ~(0xFF << 4);
    GPIOA_CRH |= (0xB << 4) | (0x4 << 8);

    USART1_BRR = 0x341; /* baud rate is 9600 (for fCK = 8MHz)*/

    USART1_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

/**
 * TODO: Non-blocking IO
 */
void USART1_putchar(int c)
{
    while (!(USART1_SR & USART_SR_TXE))
        ;
    USART1_DR = c;
}

long USART1_getchar(void)
{
    while (!(USART1_SR & USART_SR_RXNE))
        ;
    long c = USART1_DR;
    ;
    return c;
}