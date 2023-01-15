
all:
	@echo 'Nothing to build'
	@echo ''

clean:
	rm -rf *.o *.elf

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $(BUILD_DIR)/$@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $(BUILD_DIR)/$@
