#include "fb.h"
#include "io.h"

static char *fb = (char *)FB_BASE_ADDRESS;
static unsigned short cursor_pos;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[2 * i] = c;
    fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void move_cursor_forward(void) {
    cursor_pos++;
    fb_move_cursor(cursor_pos);
}

int fb_write(char *buf, unsigned int len) {
    for (unsigned i = 0; i < len; i++) {
        fb_write_cell(i, buf[i], FB_COLOR_DARK_GREY, FB_COLOR_GREEN);
        move_cursor_forward();
    }
    return 0;
}
