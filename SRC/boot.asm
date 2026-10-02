bits 32

section .multiboot
align 4

multiboot_header:
    dd 0x1BADB002                ; magic
    dd 0x00000003                ; flags
    dd -(0x1BADB002 + 0x00000003) ; checksum

extern kmain
extern load_gdt
extern load_idt
section .text
global _start

;set segment registers and call kmain

_start:
    call load_gdt

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.reload

    .reload:
        call load_idt

        call kmain

    .hang:
        cli
        hlt
        jmp .hang
