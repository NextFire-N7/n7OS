#include <n7os/time.h>
#include <n7OS/cpu.h>
#include <n7OS/irq.h>
#include <inttypes.h>
#include <stdio.h>

extern void handler_IT_timer();

int i = 0;
char 

void demasquer()
{
    outb(inb(PIC_DATA_PORT) & ~(1 << IRQ_PORT_NUM), PIC_DATA_PORT);
}

void masquer()
{
    outb(inb(PIC_DATA_PORT) | (1 << IRQ_PORT_NUM), PIC_DATA_PORT);
}

void init_timer()
{
    outb(PIT_CONFIG, PIT_REG_PORT);
    outb(FREQUENCE & 0xFF, PIT_CH0_PORT);
    outb(FREQUENCE >> 8, PIT_CH0_PORT);
    init_irq_entry(TIMER_IT, (uint32_t)handler_IT_timer);
    demasquer();
}

void handler_it_timer()
{
    masquer();
    printf("\r%i", i++);
    outb(0x20, PIC_CMD_PORT);
    demasquer();
}