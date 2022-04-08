#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>

void kernel_start(void)
{

    // on ne doit jamais sortir de kernel_start
    while (1)
    {
        printf("Hello world!\n");
        // cette fonction arrete le processeur
        hlt();
    }
}
