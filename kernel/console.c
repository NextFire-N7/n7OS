#include <n7OS/console.h>
#include <n7OS/cpu.h>

typedef unsigned char uint8_t;

int cursor_pos = 0;

void console_putcursor()
{
    int pos = 0xB8000 + cursor_pos * 2;
    outb(0xF, 0x3D4);
    outb(pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb(pos >> 0xF, 0x3D5);
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
        break;

    case '\r':
        cursor_pos -= cursor_pos % 80;
        break;

    default:
        if (c > 31 && c < 127)
        {
            uint8_t *scr_tab = (uint8_t *)0xB8000;
            int pos = 0xB8000 + cursor_pos * 2;
            scr_tab[pos] = (0x0F << 8) | c;
            cursor_pos++;
        }
        break;
    }
    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}
