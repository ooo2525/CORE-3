#ifndef ATA_H
#define ATA_H

#include <stdint.h>

void read_sectors(uint32_t sector_count, uint32_t lba, uint8_t drive, uint8_t *buffer);
void write_sectors(uint32_t sector_count, uint32_t lba, uint8_t drive, uint8_t *buffer);

#endif
