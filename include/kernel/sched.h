#include "arch.h"
#include "kernel/libc.h"
#include "kernel/list.h"

typedef struct {
    context_t context;
    void *stack;
    list_node_t list;
} task_t;

void sched_init(void);

void yield(void);

void sched_next_task(void);

task_t *proc_create(void (*func)(void), void *stack);
