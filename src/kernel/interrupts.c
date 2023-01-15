#include "interrupts.h"
#include "fb.h"
#include "keyboard.h"
#include "pic.h"
#include "serial.h"

#define INTERRUPTS_KEYBOARD 33
#define INTERRUPTS_DESCRIPTOR_COUNT 256
struct IDT idt;
struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
unsigned short shift_pressed = 0x00;

void interrupts_init_descriptor(int index, unsigned int address) {
  idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF;
  idt_descriptors[index].offset_low = (address & 0xFFFF);
  idt_descriptors[index].segment_selector = 0x08;
  idt_descriptors[index].reserved = 0x00;
  idt_descriptors[index].type_and_attr = (0x01 << 7) |               // P
                                         (0x00 << 6) | (0x00 << 5) | // DPL
                                         0xe;
}

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu,
                       unsigned int interrupt,
                       __attribute__((unused)) struct stack_state stack) {
  unsigned char scan_code;
  unsigned char ascii;

  switch (interrupt) {
  case INTERRUPTS_KEYBOARD:
    scan_code = keyboard_read_scan_code();

    if (scan_code == 42) { // shift
      shift_pressed = !shift_pressed;
    } else if (scan_code <= KEYBOARD_MAX_ASCII) {
      ascii = keyboard_scan_code_to_ascii(scan_code);
      if (shift_pressed) {
        shift_pressed = 0;
        if (ascii >= 'a' && ascii <= 'z') {
          ascii -= 32; // to uppercase
        }
      }
      char str[1];
      str[0] = ascii;
      if (scan_code == 14) {
        fb_put_b(FB_BACKSPACE_ASCII);
      } else {
        serial_write(COM1, str, 1);
        fb_put_b(ascii);
      }
    }
    pic_acknowledge(interrupt);
    break;
  default:
    break;
  }
}

void install_idt() {

  interrupts_init_descriptor(INTERRUPTS_KEYBOARD,
                             (unsigned int)(long)interrupt_handler_33);
  idt.address = (unsigned int)(long)&idt_descriptors;
  idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
  load_idt((unsigned int)(long)&idt);
  pic_remap();
}
