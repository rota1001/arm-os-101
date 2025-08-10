#include "user/syscall.h"
#include "kernel/libc.h"

unsigned long syscall(unsigned long num,
                      unsigned long a0,
                      unsigned long a1,
                      unsigned long a2)
{
    register unsigned long r0 asm("r0") = num;
    register unsigned long r1 asm("r1") = a0;
    register unsigned long r2 asm("r2") = a1;
    register unsigned long r3 asm("r3") = a2;
    asm volatile("svc 0"
                 : "+r"(r3)
                 : "r"(r0), "r"(r1), "r"(r2)
                 : "lr", "memory");
    return r3;
}