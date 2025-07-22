#include "kernel/regs.h"
#include "kernel/usart.h"
extern void kernel_main(void);

extern unsigned long _etext, _data, _edata, _bss, _ebss, _text_lma, _text,
    _estack;

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


__attribute__((section(".isr_vector"))) unsigned long vector[] = {
    (unsigned long) &_estack, (unsigned long) reset_isr};
