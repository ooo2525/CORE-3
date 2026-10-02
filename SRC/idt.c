#include <stdint.h>

//asm externs
extern void dum1(void);
extern void dum2(void);
extern void int0x60(void);
extern void keyboard(void);

struct __attribute__((packed)) entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
};

struct __attribute__((packed)) idt_descriptor {
    uint16_t limit;
    uint32_t base;
};

struct entry idt [256];

void load_idt() {
    //int 0x60 = OS API interrupt
    struct entry int60;
    int60.offset_low = (uint32_t)int0x60 & 0xFFFF;
    int60.offset_high  = ((uint32_t)int0x60 >> 16) & 0xFFFF;
    int60.selector = 0x08;
    int60.zero = 0;
    int60.type_attr = 0xEE;
    idt[0x60] = int60;

    //interrupts that push an error
    struct entry error;
    error.offset_low = (uint32_t)dum2 & 0xFFFF;
    error.offset_high = ((uint32_t)dum2 >> 16) & 0xFFFF;
    error.selector = 0x08;
    error.zero = 0;
    error.type_attr = 0x8E;
    idt[8] = error;
    for (int i = 10; i <= 14; i++)
    {
        idt[i] = error;
    }
    
    //interrupts that don't push an error
    struct entry normal;
    normal.offset_low = (uint32_t)dum1 & 0xFFFF;
    normal.offset_high = ((uint32_t)dum1 >> 16) & 0xFFFF;
    normal.selector = 0x08;
    normal.zero = 0;
    normal.type_attr = 0x8E;
    idt[9] = normal;
    for (int i = 0; i <= 7; i++)
    {
        idt[i] = normal;
    }

    //keyboard interrupt
    struct entry keyb;
    keyb.offset_low = (uint32_t)keyboard & 0xFFFF;
    keyb.offset_high = ((uint32_t)keyboard >> 16) & 0xFFFF;
    keyb.selector = 0x08;
    keyb.zero = 0;
    keyb.type_attr = 0x8E;
    idt[0x21] = keyb;

    //idt descriptor
    struct idt_descriptor idt_desc;
    idt_desc.limit = 2047;
    idt_desc.base = (uint32_t)&idt[0];

    //lidt
    __asm__ volatile (
        "lidt [%0]"
        :
        :"r" (&idt_desc)
    );

    return;
}
