#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>

void kernel_start(void)
{

    // on ne doit jamais sortir de kernel_start
    while (1)
    {
        // test de l'affichage
        printf("\f");
        for (int i = 0; i < 30; i++)
            printf("hello world\t%i\n", i);
        printf("hello world\tbloup\nhave a nice day!");

        // test des interruptions
        init_irq();
        __asm__("int $50" ::);

        // cette fonction arrete le processeur
        hlt();
    }
}
