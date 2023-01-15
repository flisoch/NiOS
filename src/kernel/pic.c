#include "pic.h"
#include "io.h"
void pic_acknowledge(unsigned int interrupt)
{
    if(interrupt < PIC_1_OFFSET || interrupt > PIC_2_END) {
        return;
    }

    if (interrupt < PIC_2_OFFSET) {
        outb(PIC_1_COMMAND_PORT, PIC_ACKNOWLEDGE);
    }
    else {
        outb(PIC_2_COMMAND_PORT, PIC_ACKNOWLEDGE);
    }
}

void pic_remap()
{
    /* ICW1 */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    /* ICW2 */
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    /* ICW3 */
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    /* ICW4 */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    /* pic mask */
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);

    asm("sti"); // Enable interrupts.
}

