#include "rcc.h"

void rcc_init(void)
{
    SET_REG_FIELD(RCC->CR, RCC_CR_HSEON, 1); /* Turn on HSE */
    while (!GET_REG_FIELD(RCC->CR, RCC_CR_HSERDY))
        ; /* Wait for ready */

    SET_REG_FIELD(FLASH->ACR, FLASH_ACR_LATENCY, 2);
    SET_REG_FIELD(FLASH->ACR, FLASH_ACR_PRFTBE, 1);

    SET_REG_FIELD(RCC->CFGR, RCC_CFGR_PLLSRC, 1); /* Set PLL source to HSE */
    SET_REG_FIELD(RCC->CFGR, RCC_CFGR_PLLMUL,
                  0b0110); /* set PLL multiplication factor to 8 */
    SET_REG_FIELD(RCC->CR, RCC_CR_PLLON, 1);
    while (!GET_REG_FIELD(RCC->CR, RCC_CR_PLLRDY))
        ;

    SET_REG_FIELD(RCC->CFGR, RCC_CFGR_PPRE2, 0b110); /* HCLK divided by 8 */
    SET_REG_FIELD(RCC->CFGR, RCC_CFGR_SW, 2); /* PLL selected as system clock */
    while (GET_REG_FIELD(RCC->CFGR, RCC_CFGR_SWS) != 2)
        ;
}
