#include "context.h"


__attribute__((naked)) int setjmp(context_t *ctx)
{
    asm volatile(
        "str r4, [r0]\n"
        "str r5, [r0, #4]\n"
        "str r6, [r0, #8]\n"
        "str r7, [r0, #12]\n"
        "str r8, [r0, #16]\n"
        "str r9, [r0, #20]\n"
        "str r10, [r0, #24]\n"
        "str r11, [r0, #28]\n"
        "str lr, [r0, #32]\n"
        "str sp, [r0, #36]\n"
        "mov r0, 0\n"
        "bx lr\n"
        :
        :
        : "memory");
}

__attribute__((naked)) void longjmp(context_t *ctx)
{
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
        "mov r0, 1\n"
        "bx lr\n"
        :
        :
        : "memory");
}
