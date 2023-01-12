OBJECTS = loader.o kmain.o gdt.o gdt_asm.o fb.o serial.o io.o\
		pic.o interrupts.o interrupts_asm.o keyboard.o
BUILD_DIR = ./build
OBJECTS_WITH_PREFIX = $(addprefix $(BUILD_DIR)/, $(OBJECTS)) 
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS_WITH_PREFIX) -o $(BUILD_DIR)/kernel.elf

os.iso: kernel.elf
	cp $(BUILD_DIR)/kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $(BUILD_DIR)/$@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/os.iso
	# rm -rf *.o kernel.elf os.iso
