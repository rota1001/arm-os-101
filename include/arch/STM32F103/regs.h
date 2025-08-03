#pragma once

/* Programmer has to ensure the VALUE is valid */
#define SET_REG_FIELD(REG, FIELD, VALUE)                              \
    do {                                                              \
        (REG) = ((REG) & ~(FIELD##_MASK)) | ((VALUE) << FIELD##_POS); \
    } while (0)

#define GET_REG_FIELD(REG, FIELD) (((REG) & FIELD##_MASK) >> FIELD##_POS)

#define DEFINE_REG_FIELD(FIELD, POS, WIDTHMASK) \
    enum { FIELD##_POS = (POS), FIELD##_MASK = ((WIDTHMASK) << (POS)) }


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

struct rcc {
    volatile unsigned long CR;
    volatile unsigned long CFGR;
    volatile unsigned long CIR;
    volatile unsigned long APB2RSTR;
    volatile unsigned long APB1RSTR;
    volatile unsigned long AHBENR;
    volatile unsigned long APB2ENR;
    volatile unsigned long APB1ENR;
    volatile unsigned long BDCR;
    volatile unsigned long CSR;
};


DEFINE_REG_FIELD(RCC_CR_HSION, 0, 0x1);
DEFINE_REG_FIELD(RCC_CR_HSIRDY, 1, 0x1);
/* Reserved : 1 */
DEFINE_REG_FIELD(RCC_CR_HSITRIM, 3, 0x1f);
DEFINE_REG_FIELD(RCC_CR_HSICAL, 8, 0xff);
DEFINE_REG_FIELD(RCC_CR_HSEON, 16, 0x1);
DEFINE_REG_FIELD(RCC_CR_HSERDY, 17, 0x1);
DEFINE_REG_FIELD(RCC_CR_HSEBYP, 18, 0x1);
DEFINE_REG_FIELD(RCC_CR_CSSON, 19, 0x1);
/* Reserved : 4 */
DEFINE_REG_FIELD(RCC_CR_PLLON, 24, 0x1);
DEFINE_REG_FIELD(RCC_CR_PLLRDY, 25, 0x1);

DEFINE_REG_FIELD(RCC_CFGR_SW, 0, 0x3);
DEFINE_REG_FIELD(RCC_CFGR_SWS, 2, 0x3);
DEFINE_REG_FIELD(RCC_CFGR_HPRE, 4, 0xf);
DEFINE_REG_FIELD(RCC_CFGR_PPRE1, 8, 0x7);
DEFINE_REG_FIELD(RCC_CFGR_PPRE2, 11, 0x7);
DEFINE_REG_FIELD(RCC_CFGR_ADCPRE, 14, 0x3);
DEFINE_REG_FIELD(RCC_CFGR_PLLSRC, 16, 0x1);
DEFINE_REG_FIELD(RCC_CFGR_PLLXTPRE, 17, 0x1);
DEFINE_REG_FIELD(RCC_CFGR_PLLMUL, 18, 0xf);
DEFINE_REG_FIELD(RCC_CFGR_USBPRE, 22, 0x1);
/* Reserved : 1 */
DEFINE_REG_FIELD(RCC_CFGR_MCO, 24, 0x7);
/* Reserved : 5 */

DEFINE_REG_FIELD(RCC_APB2ENR_AFIOEN, 0, 0x1);
/* Reserved : 1 */
DEFINE_REG_FIELD(RCC_APB2ENR_IOPAEN, 2, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPBEN, 3, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPCEN, 4, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPDEN, 5, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPEEN, 6, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPFEN, 7, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_IOPGEN, 8, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_ADC1EN, 9, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_ADC2EN, 10, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_TIM1EN, 11, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_SPI1EN, 12, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_TIM8EN, 13, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_USART1EN, 14, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_ADC3EN, 15, 0x1);
/* Reserved : 3 */
DEFINE_REG_FIELD(RCC_APB2ENR_TIM9EN, 19, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_TIM10EN, 20, 0x1);
DEFINE_REG_FIELD(RCC_APB2ENR_TIM11EN, 21, 0x1);
/* Reserved : 10 */

DEFINE_REG_FIELD(RCC_APB1ENR_AFIOEN, 0, 0x1);
/* Reserved : 1 */
DEFINE_REG_FIELD(RCC_APB1ENR_IOPAEN, 2, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPBEN, 3, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPCEN, 4, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPDEN, 5, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPEEN, 6, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPFEN, 7, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_IOPGEN, 8, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_ADC1EN, 9, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_ADC2EN, 10, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_TIM1EN, 11, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_SPI1EN, 12, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_TIM8EN, 13, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_USART1EN, 14, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_ADC3EN, 15, 0x1);
/* Reserved : 3 */
DEFINE_REG_FIELD(RCC_APB1ENR_TIM9EN, 19, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_TIM10EN, 20, 0x1);
DEFINE_REG_FIELD(RCC_APB1ENR_TIM11EN, 21, 0x1);
/* Reserved : 10 */

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

struct flash_regs {
    volatile unsigned long ACR;
    volatile unsigned long KEYR;
    volatile unsigned long OPTKEYR;
    volatile unsigned long SR;
    volatile unsigned long CR;
    volatile unsigned long AR;
    volatile unsigned long RESERVED;
    volatile unsigned long OBR;
    volatile unsigned long WRPR;
    /* something more */
};

#define FLASH_BASE (0x40022000)
#define FLASH ((struct flash_regs *) FLASH_BASE)

DEFINE_REG_FIELD(FLASH_ACR_LATENCY, 0, 0b111);
DEFINE_REG_FIELD(FLASH_ACR_HLFCYA, 3, 1);
DEFINE_REG_FIELD(FLASH_ACR_PRFTBE, 4, 1);
DEFINE_REG_FIELD(FLASH_ACR_PRFTBS, 5, 1);
