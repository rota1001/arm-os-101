#include "arch.h"
#include "kernel/libc.h"

int kernel_main()
{
    usb0_init();
    mm_init();
    while (!usb0_available())
        ;
    PANIC("unreachable");
}
