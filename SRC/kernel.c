#include "vga.h"
#include "memory.h"

//main file
extern volatile unsigned char key;

void kmain(void)
{
    //initialize the pic and ps2 keyboard
    //basically a lot of initialization and prot i/o
    __asm__ volatile (
        "mov al , 0x11\n"
        "out 0x20, al\n"
        "out 0xA0, al\n"
        "mov al, 0x20\n"
        "out 0x21, al\n"
        "mov al, 0x28\n"
        "out 0xA0, al\n"
        "mov al, 0x04\n"
        "out 0x21, al\n"
        "mov al, 0x02\n"
        "out 0xA1, al\n"
        "mov al, 0x01\n"
        "out 0x21, al\n"
        "out 0xA1, al\n"
        "mov al, 0xFD\n"
        "out 0x21, al\n"
        "mov al, 0xFF\n"
        "out 0xA1, al\n"
        "mov al, 0xAE\n"
        "out 0x64, al\n"
        "check:\n"
        "in al, 0x64\n"
        "test al, 0x02\n"
        "jnz check\n"
        "mov al, 0xF4\n"
        "out 0x60, al\n"
        "checkc:\n"
        "in al, 0x64\n"
        "test al, 1\n"
        "jz checkc\n"
        "in al, 0x60\n"
        "mov al, 0x20\n"
        "out 0x64, al\n"
        "checkb:\n"
        "in al, 0x64\n"
        "test al, 1\n"
        "jz checkb\n"
        "in al, 0x60\n"
        "or al, 1\n"
        "push ax\n"
        "mov al, 0x60\n"
        "out 0x64, al\n"
        "pop ax\n"
        "out 0x60, al\n"
        "sti"
        :
        :
        :"ax"
    );

    //debug print if everyhting still wokrs
    printc("works", 0x0F);

    //infinite loop so it dosnt exit
    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
