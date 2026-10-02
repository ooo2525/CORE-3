#include <stdint.h>

extern unsigned char kernel_end;
unsigned char *heap_current = &kernel_end;

//very simple memory allocation

unsigned char *kmalloc(uint32_t size) {
    unsigned char *first_byte = heap_current;
    heap_current += size;
    return first_byte;
}
