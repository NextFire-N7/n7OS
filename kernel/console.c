#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <malloc.h>

console_entry *scr_tab = (console_entry *)0xB8000;
int pos = 0;

void console_slide()
{
    memcpy(scr_tab,
           scr_tab + MAX_COL,
           (MAX_COL * (MAX_LINE - 1)) * sizeof(console_entry));
    memset(scr_tab + MAX_COL * (MAX_LINE - 1),
           FORMAT << 8 | ' ',
           MAX_COL * sizeof(console_entry));
    pos = MAX_COL * (MAX_LINE - 1);
}

void console_putcursor()
{
    scr_tab[pos] = FORMAT << 8 | (scr_tab[pos] & 0xFF);
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
        pos += MAX_COL - pos % MAX_COL;
        break;

    case '\f':
        memset(scr_tab,
               FORMAT << 8 | ' ',
               MAX_COL * MAX_LINE * sizeof(console_entry));
        pos = 0;
        break;

    case '\r':
        pos -= pos % MAX_COL;
        break;

    default:
        if (c > 31 && c < 127)
            scr_tab[pos++] = FORMAT << 8 | c;
        break;
    }

    if (pos == MAX_COL * MAX_LINE)
        console_slide();

    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}
