#include "serial.h"
#include "io.h"

/* ports */
#define DATA_PORT(port) port
#define FIFO_CONTROL_PORT(port) port + 2
#define LINE_CONTROL_PORT(port) port + 3
#define MODEM_CONTROL_PORT(port) port + 4
#define LINE_STATUS_PORT(port) port + 5
#define DLAB_LOW_BYTE_PORT(port) port
#define DLAB_HIGH_BYTE_PORT(port) port + 1

/* constants*/
#define ENABLE_DLAB 0x80

void serial_configure_baud_rate(unsigned short com,
                                unsigned short baud_rate_divisor) {
  outb(LINE_CONTROL_PORT(com), ENABLE_DLAB);
  outb(DLAB_LOW_BYTE_PORT(com), baud_rate_divisor & 0x00FF);
  outb(DLAB_HIGH_BYTE_PORT(com), (baud_rate_divisor & 0xFF00) >> 8);
}

void serial_configure_line(unsigned short com) {
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   * data length of 8 bits, one stop bit, no parity bit, break control
   * disabled and DLAB disabled
   */
  outb(LINE_CONTROL_PORT(com), 0x03);
}

void serial_configure_fifo_buffer(unsigned short com) {
  /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
   * Content: | lvl | bs | r | dma | clt | clr | e |
   * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
   */
  outb(FIFO_CONTROL_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com) {
  /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
   * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
   * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1 | = 0x03
   */
  outb(MODEM_CONTROL_PORT(com), 0x03);
}

void serial_init(unsigned short com, unsigned short baud_rate_divisor) {
  serial_configure_baud_rate(com, baud_rate_divisor);
  serial_configure_line(com);
  serial_configure_fifo_buffer(com);
  serial_configure_modem(com);
}

static int is_transmit_fifo_empty(unsigned short com) {
  /* 0x20 = bit 5: 1 if XMIT fifo is empty */
  return inb(LINE_STATUS_PORT(com)) & 0x20;
}
void serial_write_byte(unsigned short com, unsigned char data) {
  while (!is_transmit_fifo_empty(com)) {
    /* wait and try again*/
  }
  outb(DATA_PORT(com), data);
}

int serial_write(unsigned short com, char *buf, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    serial_write_byte(com, buf[i]);
  }
  return 0;
}
