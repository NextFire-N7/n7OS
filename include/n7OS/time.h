#ifndef TIME_H
#define TIME_H

#define PIT_CH0_PORT 0x40
#define PIT_CH1_PORT 0x41
#define PIT_CH2_PORT 0x42
#define PIT_REG_PORT 0x43

#define PIT_CONFIG 0x34

#define IRQ_PORT_NUM 0
#define TIMER_IT 0x20

#define PIC_CMD_PORT 0x20
#define PIC_DATA_PORT 0x21

#define FREQUENCE 1193 // 1.19 MHz / 1 kHz

void init_timer();

#endif
