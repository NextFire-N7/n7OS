#include <stdio.h>
#include <n7OS/cpu.h>
#include <unistd.h>

void init()
{
    while (1)
    {
        printf("Hello, world from init\n");
        // schedule();
        hlt();
    }
}
