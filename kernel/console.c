#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <malloc.h>

console_entry *scr_tab = (console_entry *)0xB8000;
int pos = 0;

void console_slide()
{
    for (int i = 0; i < MAX_POS - NB_COL; i++)
        scr_tab[i] = scr_tab[i + NB_COL];
    for (int i = MAX_POS - NB_COL; i < MAX_POS; i++)
        scr_tab[i] = FORMAT << 8;
    pos = MAX_POS - NB_COL;
}

void console_putcursor()
{
    outb(0xF, 0x3D4);
    outb(pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb((pos >> 8) & 0xFF, 0x3D5);
}

void console_putchar(char c)
{
    switch (c)
    {
    case '\b':
        pos -= 1;
        break;

    case '\t':
        pos += 8;
        break;

    case '\n':
        pos += NB_COL - pos % NB_COL;
        break;

    case '\f':
        for (int i = 0; i < MAX_POS; i++)
            scr_tab[i] = FORMAT << 8;
        pos = 0;
        break;

    case '\r':
        pos -= pos % NB_COL;
        break;

    default:
        if (c > 31 && c < 127)
            scr_tab[pos++] = FORMAT << 8 | c;
        break;
    }

    if (pos == MAX_POS)
        console_slide();

    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}
