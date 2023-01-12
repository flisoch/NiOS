global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

section .bss
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel


section .text                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax

    mov esp, kernel_stack + KERNEL_STACK_SIZE 
    extern sum_of_three
    extern kmain
    
    push dword 3
    push dword 2
    push dword 1
    call sum_of_three
    mov ebx, eax
    
    ; mov dx, 0x3D4
    ; mov al, 14
    ; out dx, al
    ; mov dx, 0x3D5
    ; mov al, 0x00
    ; out dx, al

    ; mov dx, 0x3D4
    ; mov al, 15
    ; out dx, al
    ; mov dx, 0x3D5
    ; mov al, 0x50
    ; out dx, al

    ;mov word [0x000B8000], 0x2841
    ;mov word [0x000B8010], 0x2842

    call kmain

.loop:
    jmp .loop                   ; loop forever
