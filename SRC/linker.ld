ENTRY(_start)

SECTIONS
{
    . = 0x700;

    .text : {
        *(.multiboot)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    kernel_end = .;
}
