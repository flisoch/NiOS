#include "fb.h"
#include "interrupts.h"
#include "serial.h"
#include "gdt.h"
#include "multiboot.h"

int sum_of_three(int arg1, int arg2, int arg3) { return arg1 + arg2 + arg3; }

void init() {
    serial_init(COM1, Baud_115200);
    gdt_init();
    install_idt();
}

void print_hello_world() {
    char message[] = "Life's good\n";
    serial_write(COM1, message, sizeof(message ) - 1);
}

void kmain(unsigned int ebx) {
    init();
    print_hello_world();

    multiboot_info_t *mbinfo = (multiboot_info_t *)(long)ebx;
    multiboot_module_t* modules = (multiboot_module_t*)(long)mbinfo->mods_addr;
    unsigned int mod_addr = modules->mod_start;

    if ((mbinfo->mods_count) == 1) {
        char message[] = "ONE module loaded successfully";
        serial_write(COM1, message, sizeof(message)-1);

        typedef void(*call_module_t)(void);
        call_module_t start_program = (call_module_t)(long) mod_addr;
        start_program();
    }
    else if (mbinfo->mods_count == 0) {
        char message[] = "Error: No modules loaded";
        serial_write(COM1, message, sizeof(message)-1);
    }
    else {
        char message[] = "Error: More than One module loaded";
        serial_write(COM1, message, sizeof(message)-1);
    }
}