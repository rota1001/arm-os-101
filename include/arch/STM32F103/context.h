#pragma once
typedef struct context {
    unsigned long r4, r5, r6, r7, r8, r9, r10, r11;
    unsigned long lr;  /* return address */
    unsigned long psp; /* stack pointer */
} context_t;

int setjmp(context_t *ctx);

__attribute__((noreturn)) void longjmp(context_t *ctx);
