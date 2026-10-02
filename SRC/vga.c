#include <stdint.h>

int o = 0;
volatile unsigned short *video = (unsigned short *)0xB8000;

//printing directly to vga text mode memory

void printc(unsigned char *str, uint8_t color) {
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            o = ((0 / 80) + 1) * 80;
        }
        else
        {
            video[o] = ((uint16_t)color << 8) | str[i];
            o++;
        }
        i++;  
    }
}
