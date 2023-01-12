#include "fb.h"
#include "interrupts.h"
#include "serial.h"
#include "gdt.h"

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

void init() {
    serial_init(COM1, Baud_115200);
    gdt_init();
    install_idt();
}

void kmain() {
    init();
    char buf[] = " Life's good ";
    fb_write(buf, 14);
    serial_write(COM1, buf, 13);
}