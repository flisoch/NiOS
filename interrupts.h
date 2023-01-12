#ifndef INTERRUPTS_H
#define INTERRUPTS_H

struct IDT {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

struct IDTDescriptor {
    unsigned short offset_low;
    unsigned short segment_selector;

    unsigned char reserved;
    unsigned char type_and_attr;
    unsigned short offset_high;
} __attribute__((packed));

struct cpu_state {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
} __attribute__((packed));

struct stack_state {
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);
void install_idt();
void load_idt(unsigned int idt_address);
void interrupt_handler_33();
void interrupt_handler_14();

#endif /* INTERRUPTS_H */
