#ifndef SERIAL_H
#define SERIAL_H

#define COM1 0x3F8

/* Divisor for different baud rates */
enum BaudRate { Baud_115200 = 1, Baud_57600 = 2, Baud_38400 = 3, Baud_19200 = 6, Baud_9600 = 12};

void serial_init(unsigned short com, unsigned short baud_rate_divisor);
void serial_write_byte(unsigned short com, unsigned char data);
unsigned char serial_read_byte(unsigned short com);
int serial_write(unsigned short com, char* buf, unsigned int len);

#endif /* SERIAL_H */
