#include <inttypes.h>
#include <n7OS/irq.h>
#include <stdio.h>

void init_irq_entry(int irq_num, uint32_t addr)
{
    idt_entry_t *entry = (idt_entry_t *)&idt[irq_num];
    entry->offset_inf = addr & 0xFFFF;
    entry->offset_sup = (addr >> 16) & 0xFFFF;
    // segment selector
    entry->sel_segment = KERNEL_CS;
    // zero
    entry->zero = 0;
    // P=0b1; DPL=0b00; S=0b0; GateType=0b1110 (32-bit Interrupt Gate)
    entry->type_attr = 0x8E;
}

