#include <n7OS/console.h>
#include <n7OS/cpu.h>

console_entry *scr_tab = (console_entry *)0xB8000;
int pos = 0; // cursor position

// Slide the screen up one line
void console_slide()
{
    for (int i = 0; i < MAX_POS - NB_COL; i++)
        scr_tab[i] = scr_tab[i + NB_COL];
    for (int i = MAX_POS - NB_COL; i < MAX_POS; i++)
        scr_tab[i] = FORMAT << 8;
    pos = MAX_POS - NB_COL;
}

// Position the cursor at pos
void console_putcursor()
{
    outb(0xF, 0x3D4);
    outb(pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb((pos >> 8) & 0xFF, 0x3D5);
}

// Put a character at the cursor position
void console_putchar(char c)
{
    switch (c)
    {
    case '\b': // backward
        pos -= 1;
        break;

    case '\t': // tab
        pos += 8;
        break;

    case '\n': // new line
        pos += NB_COL - pos % NB_COL;
        break;

    case '\f': // flush
        for (int i = 0; i < MAX_POS; i++)
            scr_tab[i] = FORMAT << 8;
        pos = 0;
        break;

    case '\r': // return to beginning of line
        pos -= pos % NB_COL;
        break;

    default: // print the character
        if (c > 31 && c < 127)
            scr_tab[pos++] = FORMAT << 8 | c;
        break;
    }

    // slide the screen if needed
    if (pos == MAX_POS)
        console_slide();

    // update the cursor position
    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}
