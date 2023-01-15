OBJECTS = loader.o kmain.o gdt.o gdt_asm.o fb.o serial.o io.o\
		pic.o interrupts.o interrupts_asm.o keyboard.o
BUILD_DIR = ../../build
OBJECTS_WITH_PREFIX = $(addprefix $(BUILD_DIR)/, $(OBJECTS)) 
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $<

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf
	

clean:
	rm -rf *.o kernel.elf