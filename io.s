SECTION .text

global outb
outb:
    mov al, [ss:esp + 8]
    mov dx, [ss:esp + 4]
    out dx, al
    ret

global inb
inb:
    mov dx, [ss:esp + 4]
    in al, dx
    ret