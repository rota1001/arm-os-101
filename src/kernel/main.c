#include "kernel/debug.h"
#include "kernel/libc.h"
#include "kernel/usb.h"


int kernel_main()
{
    usb0_init();
    while (!usb0_available())
        ;
    PANIC("unreachable");
}
