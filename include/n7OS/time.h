#ifndef TIME_H
#define TIME_H

// ports du PIT

#define PIT_CH0_PORT 0x40
#define PIT_CH1_PORT 0x41
#define PIT_CH2_PORT 0x42
#define PIT_REG_PORT 0x43

// config PIT
// Channel 0, accès poids faible/poids fort,
// générateur d’impulsion, fréquence définie en binaire
#define PIT_CONFIG 0x34

// PIC timer
#define IRQ_PORT_NUM 0
#define TIMER_IT 0x20

// ports du PIC
#define PIC_CMD_PORT 0x20
#define PIC_DATA_PORT 0x21

// fréquence timer
#define FREQUENCE 1190 // 1.19 MHz / 1 kHz

// période round robin
#define RR_PERIOD 2000 // 2s

void init_timer();

#endif
