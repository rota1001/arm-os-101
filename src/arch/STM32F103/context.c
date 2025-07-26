#include "context.h"

int setjmp(context_t *ctx)
{
    asm volatile(
        "STR r4, [%[ctx]]\n"
        "STR r5, [%[ctx], #4]\n"
        "STR r6, [%[ctx], #8]\n"
        "STR r7, [%[ctx], #12]\n"
        "STR r8, [%[ctx], #16]\n"
        "STR r9, [%[ctx], #20]\n"
        "STR r10, [%[ctx], #24]\n"
        "STR r11, [%[ctx], #28]\n"
        "STR lr, [%[ctx], #32]\n"
        "mrs r0, psp\n"
        "STR r0, [%[ctx], #36]\n"
        :
        : [ctx] "r"(ctx)
        : "memory");
    return 0;
}

__attribute__((noreturn)) void longjmp(context_t *ctx)
{
    asm volatile(
        "LDR r4, [%[ctx]]\n"
        "LDR r5, [%[ctx], #4]\n"
        "LDR r6, [%[ctx], #8]\n"
        "LDR r7, [%[ctx], #12]\n"
        "LDR r8, [%[ctx], #16]\n"
        "LDR r9, [%[ctx], #20]\n"
        "LDR r10, [%[ctx], #24]\n"
        "LDR r11, [%[ctx], #28]\n"
        "LDR lr, [%[ctx], #32]\n"
        "LDR r0, [%[ctx], #36]\n"
        "msr psp, r0\n"
        "mov r0, 1\n"
        "bx lr\n"
        :
        : [ctx] "r"(ctx)
        : "memory");
    __builtin_unreachable();
}
