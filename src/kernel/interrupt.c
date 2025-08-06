#include "kernel/libc.h"
#include "kernel/sched.h"
#include "timer.h"


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
