#include <n7os/time.h>
#include <n7OS/cpu.h>
#include <n7OS/irq.h>
#include <inttypes.h>
#include <debug.h>
#include <string.h>
#include <n7OS/console.h>

extern void handler_IT_timer();

int time = 0;

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

void print_time(int i)
{
    // ouais c'est moche
    int h, m, s, ms;
    h = i / 3600000;
    m = (i - h * 3600000) / 60000;
    s = (i - h * 3600000 - m * 60000) / 1000;
    ms = i - h * 3600000 - m * 60000 - s * 1000;
    // print
    char buf[12];
    sprintf(buf, "%02i:%02i:%02i.%03i", h, m, s, ms);
    console_putbytes_at(buf, 12, NB_COL - 12);
}

void handler_it_timer()
{
    masquer();
    print_time(time++);
    outb(0x20, PIC_CMD_PORT);
    demasquer();
}
