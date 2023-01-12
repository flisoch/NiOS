#ifndef FB_H
#define FB_H

/* framebuffer base memory address */
#define FB_BASE_ADDRESS 0x000B8000

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* supported colors */
#define FB_COLOR_GREEN 2
#define FB_COLOR_DARK_GREY 7

/**
 * @brief writes a character to framebuffer with defined foreground and background at position i
 * 
 * @param i position in framebuffer
 * @param c character to write
 * @param fg foreground color from 0 to 15
 * @param bg background color from 0 to 15
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/**
 * @brief writes the contents of the buffer buf with length len to the framebuffer
 * 
 * @param buf 
 * @param len 
 * @return int 
 */
int fb_write(char *buf, unsigned int len);
#endif /* FB_H */
