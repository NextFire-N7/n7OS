#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#define MAX_COL 80
#define MAX_LINE 25
#define FORMAT 0x2F

typedef __UINT16_TYPE__ console_entry;

/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */
void console_putbytes(const char *s, int len);

#endif
