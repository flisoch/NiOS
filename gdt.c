#include "gdt.h"
#include "serial.h"

#define SEGMENT_DESCRIPTOR_COUNT 3
#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFF

#define SEGMENT_CODE_TYPE 0x9A
#define SEGMENT_DATA_TYPE 0x92

#define SEGMENT_GRANULARITY 0xCF

gdt_entry_t gdt_entries[SEGMENT_DESCRIPTOR_COUNT];

void gdt_set_gate(int index, unsigned int base_address, unsigned int limit,
                  unsigned char access_byte, unsigned char gran) {
  gdt_entries[index].base_low = base_address & 0xFFFF;
  gdt_entries[index].base_middle = (base_address >> 16) & 0xFF;
  gdt_entries[index].base_high = (base_address >> 24) & 0xFF;
  gdt_entries[index].limit_low = limit & 0xFFFF;
  gdt_entries[index].access_byte = access_byte;
  gdt_entries[index].granularity = gran;
}

void gdt_init() {
  gdt_ptr_t gdt_ptr;
  gdt_ptr.size = (sizeof(gdt_entry_t) * 3) - 1;
  gdt_ptr.address = (unsigned int)(long)(&gdt_entries);

  gdt_set_gate(0, 0, 0, 0, 0);
  gdt_set_gate(1, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_CODE_TYPE,
               SEGMENT_GRANULARITY);
  gdt_set_gate(2, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_DATA_TYPE, SEGMENT_GRANULARITY);
  gdt_flush((unsigned)(long)&gdt_ptr);
}
