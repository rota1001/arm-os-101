#include "kernel/sched.h"

static context_t sched_context;
static list_node_t task_list;
static task_t *current;

void sched_init(void)
{
    list_init(&task_list);
}

task_t *proc_create(void (*func)(void), void *stack)
{
    task_t *task = (task_t *) malloc(sizeof(task_t));
    if (!task)
        return 0;
    memset(&task->context, 0, sizeof(task->context));
    task->context.lr = (unsigned long) func;
    task->context.psp = (unsigned long) stack;
    list_push_back(&task_list, &task->list);
    return task;
}

void yield(void)
{
    if (!setjmp(&current->context))
        longjmp(&sched_context);
}

void sched(void)
{
    while (1) {
        list_node_t *now = task_list.next;
        if (now == &task_list)
            return;
        list_remove(now);
        list_push_back(&task_list, now);
        current = container_of(now, task_t, list);
        if (!setjmp(&sched_context))
            longjmp(&current->context);
    }
}