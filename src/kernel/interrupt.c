#include "exception.h"
#include "kernel/libc.h"
#include "kernel/sched.h"


extern task_t *current;
extern int sched_ready;

__attribute__((naked)) void timer_irq_handler(void)
{
    if (!sched_ready)
        return;
    setjmp(&current->context);
    current->context.lr = (unsigned long) restore_tmp_registers;
    ret_to_sched();
}

unsigned long syscall_handler(unsigned long num,
                              unsigned long a0,
                              unsigned long a1,
                              unsigned long a2)
{
    printf("syscall%d(%d, %d, %d)\n", num, a0, a1, a2);
    return 0xdeadbeef;
}