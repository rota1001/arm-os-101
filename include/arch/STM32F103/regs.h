#pragma once

struct gpio_cr {
    volatile unsigned long MODE0 : 2;
    volatile unsigned long CNF0 : 2;
    volatile unsigned long MODE1 : 2;
    volatile unsigned long CNF1 : 2;
    volatile unsigned long MODE2 : 2;
    volatile unsigned long CNF2 : 2;
    volatile unsigned long MODE3 : 2;
    volatile unsigned long CNF3 : 2;
    volatile unsigned long MODE4 : 2;
    volatile unsigned long CNF4 : 2;
    volatile unsigned long MODE5 : 2;
    volatile unsigned long CNF5 : 2;
    volatile unsigned long MODE6 : 2;
    volatile unsigned long CNF6 : 2;
    volatile unsigned long MODE7 : 2;
    volatile unsigned long CNF7 : 2;
    volatile unsigned long MODE8 : 2;
    volatile unsigned long CNF8 : 2;
    volatile unsigned long MODE9 : 2;
    volatile unsigned long CNF9 : 2;
    volatile unsigned long MODE10 : 2;
    volatile unsigned long CNF10 : 2;
    volatile unsigned long MODE11 : 2;
    volatile unsigned long CNF11 : 2;
    volatile unsigned long MODE12 : 2;
    volatile unsigned long CNF12 : 2;
    volatile unsigned long MODE13 : 2;
    volatile unsigned long CNF13 : 2;
    volatile unsigned long MODE14 : 2;
    volatile unsigned long CNF14 : 2;
    volatile unsigned long MODE15 : 2;
    volatile unsigned long CNF15 : 2;
};

struct gpio {
    volatile struct gpio_cr CR;
    volatile unsigned long IDR;
    volatile unsigned long ODR;
    volatile unsigned long BSRR;
    volatile unsigned long BRR;
    volatile unsigned long LCKR;
};


#define GPIOA_BASE (0x40010800)
#define GPIOA ((struct gpio *) GPIOA_BASE)

#define GPIOB_BASE (0x40010C00)
#define GPIOB ((struct gpio *) GPIOB_BASE)

#define GPIOC_BASE (0x40011000)
#define GPIOC ((struct gpio *) GPIOC_BASE)

struct rcc_apb2enr {
    unsigned long AFIOEN : 1;
    unsigned long : 1;
    unsigned long IOPAEN : 1;
    unsigned long IOPBEN : 1;
    unsigned long IOPCEN : 1;
    unsigned long IOPDEN : 1;
    unsigned long IOPEEN : 1;
    unsigned long IOPFEN : 1;
    unsigned long IOPGEN : 1;
    unsigned long ADC1EN : 1;
    unsigned long ADC2EN : 1;
    unsigned long TIM1EN : 1;
    unsigned long SPI1EN : 1;
    unsigned long TIM8EN : 1;
    unsigned long USART1EN : 1;
    unsigned long ADC3EN : 1;
    unsigned long : 3;
    unsigned long TIM9EN : 1;
    unsigned long TIM10EN : 1;
    unsigned long TIM11EN : 1;
    unsigned long : 10;
};

struct rcc {
    volatile unsigned long CR;
    volatile unsigned long CFGR;
    volatile unsigned long CIR;
    volatile unsigned long APB2RSTR;
    volatile unsigned long APB1RSTR;
    volatile unsigned long AHBENR;
    volatile struct rcc_apb2enr APB2ENR;
    volatile struct rcc_apb2enr APB1ENR;
    volatile unsigned long BDCR;
    volatile unsigned long CSR;
};

#define RCC_BASE (0x40021000)
#define RCC ((struct rcc *) RCC_BASE)

enum {
    CNF_INPUT_ANALOG,
    CNF_INPUT_FLOATING,
    CNF_INPUT_PUSH_PULL,
    CNF_INPUT_RESERVED
};

enum {
    CNF_OUTPUT_GP_PUSH_PULL,
    CNF_OUTPUT_GP_OPEN,
    CNF_OUTPUT_AF_PUSH_PULL,
    CNF_OUTPUT_AF_OPEN
};

enum { MODE_INPUT, MODE_OUTPUT_10MHz, MODE_OUTPUT_2MHz, MODE_OUTPUT_50MHz };

#define GPIO_CONF(CNF, MODE) (((CNF) << 2) | (MODE))


struct usart {
    volatile unsigned long SR;
    volatile unsigned long DR;
    volatile unsigned long BRR;
    volatile unsigned long CR1;
    volatile unsigned long CR2;
    volatile unsigned long CR3;
    volatile unsigned long GTPR;
};

#define USART1_BASE (0x40013800)
#define USART1 ((struct usart *) USART1_BASE)
#define USART_SR_RXNE (1 << 5)
#define USART_SR_TC (1 << 6)
#define USART_SR_TXE (1 << 7)
#define USART_CR1_UE (1 << 13)
#define USART_CR1_TE (1 << 3)
#define USART_CR1_RE (1 << 2)
