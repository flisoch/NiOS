#ifndef IO_H
#define IO_H

/**
 * @brief Sends the given data to the given I/O port. Defined in io.s
 * 
 * @param port The I/O port to send the data to
 * @param data The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/**
 * @brief Reads the data from the given I/O port. Defined in io.s 
 * 
 * @param port The I/O port to read the data from
 * @return unsigned char - The returned data from the I/O port
 */
unsigned char inb(unsigned short port);

#endif /* IO_H */
