#include "kernel/debug.h"
#include "kernel/libc.h"
#include "kernel/regs.h"

int kernel_main()
{
    USART1_init();
    PANIC("unreachable");
}
