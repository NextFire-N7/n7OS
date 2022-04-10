#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>

void kernel_start(void)
{

    // on ne doit jamais sortir de kernel_start
    while (1)
    {
        printf("\f");
        for (int i = 0; i < 30; i++)
            printf("hello world\t%i\n", i);
        printf("hello world\tbloup\nhave a nice day!");

        // cette fonction arrete le processeur
        hlt();
    }
}
