#include <stdint.h>
#include "vga.h"

//asm externs
extern uint32_t a;
extern uint32_t b;
extern uint32_t c;
extern uint32_t d;

void int0x60_handler(void) {
    //for now only simple test will become the main OS API later
    printc("Test", 0x0F);
    return;
}
