#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>

void kernel_start(void)
{
    // test de l'affichage
    printf("\f");
    // for (int i = 0; i < 30; i++)
    //     printf("hello world\t%i\n", i);
    // printf("hello world\tbloup\nhave a nice day!");

    // init irq et test
    init_irq();
    // __asm__("int $50" ::);

    // init timer
    init_timer();

    // on ne doit jamais sortir de kernel_start
    while (1)
    {
        // cette fonction arrete le processeur
        hlt();
    }
}
