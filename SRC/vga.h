#ifndef VGA_H
#define VGA_H

#include <stdint.h>

extern int o;
extern volatile unsigned short *video;
void printc(unsigned char *str, uint8_t color);

#endif
