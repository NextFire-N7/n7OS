#include <stdio.h>
#include <n7OS/cpu.h>
#include <n7OS/process.h>

void init()
{
    while (1)
    {
        printf("Hello, world from init\n");
        scheduler();
        hlt();
    }
}
