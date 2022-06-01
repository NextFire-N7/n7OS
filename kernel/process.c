#include <n7OS/process.h>
#include <string.h>
#include <n7OS/cpu.h>
#include <stdio.h>

process_t process_table[NB_PROC];
process_t *current_process;
pid_t pid_counter = 0;

pid_t creer(const char *name, fnptr function)
{
    process_t *process;
    for (int i = 0; i < NB_PROC; i++)
    {
        process = &process_table[pid_counter];
        if (process->state == NONE)
        {
            process->pid = pid_counter;
            process->state = PRET;
            strcpy(process->name, name);
            process->stack[STACK_SIZE - 1] = (uint32_t)function;
            memset(process->ctx, 0, sizeof(process->ctx));
            process->ctx[ESP] = (uint32_t)&process->stack[STACK_SIZE - 1];
            return pid_counter;
        }
        pid_counter++;
    }
    return -1;
}

extern void ctx_sw(void *ctx_old, void *ctx_new);

void scheduler()
{
    pid_t curr_pid = getpid();
    pid_t new_pid = -1;
    pid_t npid;
    for (pid_t i = 1; i < NB_PROC; i++)
    {
        npid = (curr_pid + i) % NB_PROC;
        if (process_table[npid].state == PRET)
        {
            new_pid = npid;
            break;
        }
    }
    if (new_pid != -1)
    {
        process_table[curr_pid].state = PRET;
        process_table[new_pid].state = ELU;
        ctx_sw(&process_table[curr_pid].ctx, &process_table[new_pid].ctx);
        current_process = &process_table[new_pid];
    }
}

void arreter()
{
    current_process->state = ELU;
    scheduler();
}

void terminer()
{
    current_process->state = NONE;
    memset(current_process->stack, 0, sizeof(current_process->stack));
    scheduler();
}

pid_t getpid()
{
    return current_process->pid;
}

void init()
{
    printf("Hello, world from init\n");
    scheduler();
    while (1)
        hlt();
}

extern void processus1();

void init_process()
{
    pid_t pid_init = creer("init", (fnptr)init);
    creer("processus1", (fnptr)processus1);

    current_process = &process_table[pid_init];
    current_process->state = ELU;
    init();
}
