# CORE/3
A small kernel for the 386 CPU.

Current features:
- Multiboot compatible
- GDT
- IDT
- int 0x60 API
- ATA PIO
- VGA text mode
- PS/2 Keyboard interrupt handling
- Basic memory management.

Planned features:
- FAT 16 filesystem
- Finish int 0x60
- ring 3
- custom executable format

Int 0x60 is still in test phase and only prints Test for now.
The reason is that i want internal functions first then implement the API.
