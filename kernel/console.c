#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <malloc.h>

__UINT16_TYPE__ *scr_tab = (__UINT16_TYPE__ *)0xB8000;
int cursor_pos = 0;

void console_putcursor()
{
    outb(0xF, 0x3D4);
    outb(cursor_pos & 0xF, 0x3D5);
    outb(0xE, 0x3D4);
    outb(cursor_pos >> 0xF, 0x3D5);
}

void console_slide()
{
    memcpy(scr_tab, scr_tab + 80, 80 * 24 * 2);
    memset(scr_tab + 80 * 24, 0, 80 * 2);
    cursor_pos = 80 * 24;
}

void console_putchar(char c)
{

    switch (c)
    {
    case '\b':
        cursor_pos -= 1;
        break;

    case '\t':
        cursor_pos += 8;
        break;

    case '\n':
        cursor_pos += 80 - cursor_pos % 80;
        break;

    case '\f':
        memset(scr_tab, 0, 80 * 25 * 2);
        cursor_pos = 0;
        break;

    case '\r':
        cursor_pos -= cursor_pos % 80;
        break;

    default:
        if (c > 31 && c < 127)
            scr_tab[cursor_pos++] = (0xF << 8) | c;
        break;
    }
    if (cursor_pos == 80 * 25)
        console_slide();
    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}
