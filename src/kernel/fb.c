#include "fb.h"
#include "io.h"

#define BLACK_ON_WHITE 0x0F

#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25

#define TO_ADDRESS(row, col) (fb + 2 * (row * FB_NUM_COLS + col))

static unsigned char *fb = (unsigned char *)FB_BASE_ADDRESS;
static unsigned short cursor_pos;

static unsigned char read_cell(unsigned int row, unsigned int col) {
    unsigned char *cell = TO_ADDRESS(row, col);
    return *cell;
}

static void write_cell(unsigned char *cell, unsigned char b)
{
    cell[0] = b;
    cell[1] = BLACK_ON_WHITE;
}

void fb_write_cell_pos(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[2 * i] = c;
    fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void set_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_move_cursor(unsigned short row, unsigned short col) {
    unsigned short pos = row * FB_NUM_COLS + col;
    cursor_pos = pos;
    set_cursor(pos);
}

void move_cursor_forward(void) {
    cursor_pos++;
    set_cursor(cursor_pos);
}

void move_cursor_back(void) {
    if (cursor_pos != 0) {
        cursor_pos--;
        set_cursor(cursor_pos);
    }
}

void move_cursor_start(void) {
    cursor_pos -= cursor_pos % FB_NUM_COLS;
    set_cursor(cursor_pos);
}

void move_cursor_down(void) {
    cursor_pos += FB_NUM_COLS;
    set_cursor(cursor_pos);
}


int fb_write(char *buf, unsigned int len) {
    for (unsigned i = 0; i < len; i++) {
        fb_write_cell_pos(i, buf[i], FB_COLOR_DARK_GREY, FB_COLOR_GREEN);
        move_cursor_forward();
    }
    return 0;
}

void write_at(unsigned int row, unsigned int col, unsigned char byte) {
    unsigned char *cell = TO_ADDRESS(row, col);
    write_cell(cell, byte);
}

void scroll() {
    for (unsigned int row = 1; row < FB_NUM_ROWS; ++row) {
        for (unsigned int col = 0; col < FB_NUM_COLS; ++col) {
            write_at(row - 1, col, read_cell(row, col));
        }
    }
}

void fb_put_b(unsigned char b) {
    if (b != '\n' && b != '\t' && b!= FB_BACKSPACE_ASCII) {
        unsigned char *cell = fb + 2*cursor_pos;
        write_cell(cell, b);
    }
    
    if (b == '\n') {
        move_cursor_down();
        move_cursor_start();
    }
    else if (b == FB_BACKSPACE_ASCII) {
        move_cursor_back();
        unsigned char *cell = fb + 2 * cursor_pos;
        write_cell(cell, ' ');
    }
    else if (b == '\t') {
        for (int i = 0; i < 4; ++i) {
            fb_put_b(' ');
        }
    }
    else {
        move_cursor_forward();
    }

    if (cursor_pos >= FB_NUM_COLS * FB_NUM_ROWS) {
        scroll();
        fb_move_cursor(24, 0);
    }
}

void fb_put_s(char const *s)
{
    while (*s != '\0') {
        fb_put_b(*s++);
    }

}
void fb_put_ui(unsigned int i) {
   unsigned int digit, n;
   n = 1;
   while (n*10 <= i) {
        n *= 10;
   }
   while (n > 0) {
        digit = i / n;
        fb_put_b('0' + digit);
        i %= n;
        n /= 10;
   } 
}


void fb_put_ui_hex(unsigned int n)
{
    char *chars = "0123456789ABCDEF";
    unsigned char b = 0;
    fb_put_s("0x");

    for (int i = 7; i >= 0; --i) {
        b = (n >> i * 4) & 0x0F; 
        fb_put_b(chars[b]);
    }
}