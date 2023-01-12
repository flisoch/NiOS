#ifndef GDT_H
#define GDT_H

extern void gdt_flush(unsigned int);

struct gdt_ptr_struct {
  unsigned short size;
  unsigned int address;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

struct gdt_entry_struct {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access_byte;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

void gdt_set_gate(int index, unsigned int base_address, unsigned int limit,
                  unsigned char access_byte, unsigned char gran);
void gdt_init();

#endif /* GDT_H */
