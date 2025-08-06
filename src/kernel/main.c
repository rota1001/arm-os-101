#include "arch.h"
#include "kernel/libc.h"
#include "kernel/sched.h"
#include "rcc.h"


void proc1(void)
{
    while (1) {
        printf("proc1\n");
        for (int c = 0; c < 500000; c++)
            ;
    }
}

void proc2(void)
{
    while (1) {
        printf("proc2\n");
        for (int c = 0; c < 500000; c++)
            ;
    }
}


int kernel_main()
{
    rcc_init();
    usb0_init();
    mm_init();
    sched_init();
    timer_irq_init();
    printf("=================\n");
    char *stack1, *stack2;
    stack1 = malloc(512);
    if (!stack1)
        goto FAIL1;

    stack2 = malloc(512);
    if (!stack2)
        goto FAIL2;

    if (!proc_create(proc1, stack1 + 512))
        goto FAIL3;
    if (!proc_create(proc2, stack2 + 512))
        goto FAIL3;

    sched();
FAIL3:
    free(stack2);
FAIL2:
    free(stack1);
FAIL1:
    PANIC("unreachable");
}
