#ifndef PIC_H
#define PIC_H

#define PIC_1_OFFSET 0x20
#define PIC_2_OFFSET 0x28
#define PIC_2_END PIC_2_OFFSET + 7

#define PIC_1_COMMAND_PORT 0x20
#define PIC_2_COMMAND_PORT 0xA0
#define PIC_ACKNOWLEDGE 0x20

void pic_acknowledge(unsigned int interrupt);
void pic_remap();
#endif /* PIC_H */
