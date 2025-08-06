#pragma once
typedef struct context {
    unsigned long r4, r5, r6, r7, r8, r9, r10, r11;
    unsigned long lr; /* return address */
    unsigned long sp; /* stack pointer */
    unsigned long psr;
} context_t;

__attribute__((naked)) int setjmp(context_t *ctx);

__attribute__((noreturn)) void longjmp(context_t *ctx);
