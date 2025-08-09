#include "exception.h"
#include "kernel/sched.h"

extern context_t sched_context;

void timer_irq_init(void)
{
    SYSTICK_RELOAD = 6400000;
    SYSTICK_CURRENT = 0;
    SYSTICK_CONTROL = 0b111;
}

extern void timer_irq_handler(void);

__attribute__((naked, noreturn)) void restore_tmp_registers(void)
{
    asm volatile(
        "ldr r0, [sp, #24]\n"
        "add r0, r0, #1\n"
        "str r0, [sp, #24]\n"
        "pop {r0, r1, r2, r3, r12, lr}\n"
        "add sp, sp, #8\n"
        "ldr pc, [sp, #-8]\n");
}


__attribute__((naked, noreturn)) void ret_to_sched(void)
{
    asm volatile("mov r1, %0" ::"r"(sched));
    asm volatile(
        "ldr r0, =0x1000000\n"
        "push {r0}\n"
        "push {r1}\n"
        "add sp, sp, #-24\n"
        "mov r0, 0\n"
        "msr control, r0\n"
        "ldr lr, =0xfffffff9\n"
        "bx lr\n");
}

__attribute__((naked)) void pend_sv_irq_handler(void)
{
    unsigned long lr;
    asm volatile("mov %0, lr" : "=r"(lr));
    if (!(lr & 4))
        asm volatile("bx lr");
    timer_irq_handler();
    asm volatile(
        "ldr lr, =0xfffffff9\n"
        "bx lr\n");
}

void systick_irq_handler(void)
{
    SET_REG_FIELD(ICSR, ICSR_PENDSVSET, 1);
}

void svc_handler(void)
{
    printf("SVC\n");
}