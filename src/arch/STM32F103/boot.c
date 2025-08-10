#include "arch/STM32F103/regs.h"
#include "arch/STM32F103/usart.h"
#include "exception.h"

extern void kernel_main(void);

extern unsigned long _etext, _data, _edata, _bss, _ebss, _text_lma, _text,
    _stack_top;

__attribute__((section(".reset"))) void reset_isr()
{
    unsigned long *src = &_text_lma, *dst = &_text;
    while (dst != &_etext)
        *dst++ = *src++;

    dst = &_data;
    while (dst != &_edata)
        *dst++ = *src++;

    dst = &_bss;
    while (dst != &_ebss)
        *dst++ = 0;

    kernel_main();
    while (1)
        ;
}


#define MSP 0
#define RESET 1
#define SVC 11
#define PEND_SV 14
#define SYSTICK 15
#define TIM2_IRQ 44


__attribute__((section(".isr_vector"))) unsigned long vector[] = {
    [MSP](unsigned long) & _stack_top,
    [RESET](unsigned long) reset_isr,
    [SVC](unsigned long) svc_handler,
    [PEND_SV](unsigned long) pend_sv_irq_handler,
    [SYSTICK](unsigned long) systick_irq_handler};
