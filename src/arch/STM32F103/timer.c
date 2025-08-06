#include "timer.h"
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
    asm volatile("mov r0, %0" ::"r"(&sched_context));
    asm volatile(
        "ldr r4, [r0]\n"
        "ldr r5, [r0, #4]\n"
        "ldr r6, [r0, #8]\n"
        "ldr r7, [r0, #12]\n"
        "ldr r8, [r0, #16]\n"
        "ldr r9, [r0, #20]\n"
        "ldr r10, [r0, #24]\n"
        "ldr r11, [r0, #28]\n"
        "ldr lr, [r0, #32]\n"
        "ldr sp, [r0, #36]\n"
        "ldr r0, [r0, #40]\n"
        "push {r0}\n"
        "push {lr}\n"
        "add sp, sp, #-4\n"
        "mov r0, 1\n"
        "push {r0, r1, r2, r3, r12}\n"
        "ldr lr, =0xfffffff9\n"
        "bx lr\n");
}

__attribute__((naked)) void pend_sv_irq_handler(void)
{
    timer_irq_handler();
    asm volatile(
        "ldr lr, =0xfffffff9\n"
        "bx lr\n");
}

void systick_irq_handler(void)
{
    SET_REG_FIELD(ICSR, ICSR_PENDSVSET, 1);
}