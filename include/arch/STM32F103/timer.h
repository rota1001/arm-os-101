#include "regs.h"

void timer_irq_init(void);

void pend_sv_irq_handler(void);

void systick_irq_handler(void);

__attribute__((naked, noreturn)) void ret_to_sched(void);

__attribute__((naked, noreturn)) void restore_tmp_registers(void);
