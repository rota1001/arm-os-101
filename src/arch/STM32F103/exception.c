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

extern task_t *current;
extern unsigned long syscall_handler(unsigned long num,
                                     unsigned long a0,
                                     unsigned long a1,
                                     unsigned long a2);

__attribute__((naked)) void __syscall_handler(unsigned num,
                                              unsigned long a0,
                                              unsigned a1,
                                              unsigned a2)
{
    asm volatile(
        "bl syscall_handler\n"
        "push {r0}\n");

    asm volatile("mov r0, %0\n" ::"r"(current->user_context));
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
        "ldr r1, [r0, #36]\n"
        "pop {r3}\n"
        "msr psp, r1\n"
        "ldr r1, [r0, #44]\n"
        "msr control, r1\n"
        "push {r3}\n"
        "push {lr}\n"
        "bl free\n"
        "pop {lr}\n"
        "pop {r3}\n"
        "bx lr\n" ::
            : "memory");
}

__attribute__((naked)) void svc_handler(void)
{
    current->user_context = malloc(sizeof(context_t));
    if (!current->user_context) {
        printf("fail\n");
        goto SVC_RET;
    }

    setjmp(current->user_context);
    current->user_context->control = 3;
    register unsigned long r1 asm("r1");
    register unsigned long r2 asm("r2") = __syscall_handler;
    asm volatile(
        "mrs r0, psp\n"
        "ldr r1, [r0, #24]\n"
        "str r2, [r0, #24]\n"
        "mov r0, 2\n"
        "msr control, r0\n");
    current->user_context->lr = r1 | 1;
SVC_RET:
    asm volatile(
        "ldr lr, =0xfffffffd\n"
        "bx lr\n");
}