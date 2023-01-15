OBJECTS = program

AS = nasm
ASFLAGS = -f bin

all: $(OBJECTS)
	cp program ../../iso/modules

clean:
	rm -rf *.o *.elf $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%: %.s
	$(AS) $(ASFLAGS) $< -o $@
