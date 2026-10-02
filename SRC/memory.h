#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

extern unsigned char kernel_end;
extern unsigned char *heap_current;

unsigned char *kmalloc(uint32_t size);

#endif
