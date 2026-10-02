#include <stdint.h>

//AI used in the functions below reason: its just basic hardware level logic
//didnt want to waste time on this
void read_sectors(uint32_t sector_count, uint32_t lba, uint8_t drive, uint8_t *buffer) {
    uint8_t lba_low   = lba & 0xFF;
    uint8_t lba_mid   = (lba >> 8) & 0xFF;
    uint8_t lba_high  = (lba >> 16) & 0xFF;
    uint8_t drive_head = 0xE0 | (drive << 4) | ((lba >> 24) & 0x0F);

    asm volatile (
        "out dx, al"
        :
        : "a"((uint8_t)sector_count), "d"(0x1F2)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_low), "d"(0x1F3)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_mid), "d"(0x1F4)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_high), "d"(0x1F5)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(drive_head), "d"(0x1F6)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"((uint8_t)0x20), "d"(0x1F7)
    );

    for (uint32_t sector = 0; sector < sector_count; sector++) {

        // Wait for BSY to clear and DRQ to become set.
        uint8_t status;

        do {
            asm volatile (
                "in al, dx"
                : "=a"(status)
                : "d"(0x1F7)
            );
        } while (status & 0x80);

        if (status & 0x01)
            return;

        while (!(status & 0x08)) {
            asm volatile (
                "in al, dx"
                : "=a"(status)
                : "d"(0x1F7)
            );

            if (status & 0x01)
                return;
        }

        asm volatile (
            "mov dx, 0x1F0"
            "mov edi, %[buf]"
            "mov ecx, 256"
            "rep insw"
            :
            : [buf] "D"(buffer)
            : "ecx", "edx", "memory"
        );

        buffer += 512;
    }
}

void write_sectors(uint32_t sector_count, uint32_t lba, uint8_t drive, uint8_t *buffer) {
    uint8_t lba_low    = lba & 0xFF;
    uint8_t lba_mid    = (lba >> 8) & 0xFF;
    uint8_t lba_high   = (lba >> 16) & 0xFF;
    uint8_t drive_head = 0xE0 | (drive << 4) | ((lba >> 24) & 0x0F);

    asm volatile (
        "out dx, al"
        :
        : "a"((uint8_t)sector_count), "d"(0x1F2)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_low), "d"(0x1F3)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_mid), "d"(0x1F4)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(lba_high), "d"(0x1F5)
    );

    asm volatile (
        "out dx, al"
        :
        : "a"(drive_head), "d"(0x1F6)
    );

    /* WRITE SECTORS command */
    asm volatile (
        "out dx, al"
        :
        : "a"((uint8_t)0x30), "d"(0x1F7)
    );

    for (uint32_t sector = 0; sector < sector_count; sector++) {

        uint8_t status;

        /* Wait for BSY to clear. */
        do {
            asm volatile (
                "in al, dx"
                : "=a"(status)
                : "d"(0x1F7)
            );
        } while (status & 0x80);

        if (status & 0x01)
            return;

        /* Wait for DRQ. */
        while (!(status & 0x08)) {
            asm volatile (
                "in al, dx"
                : "=a"(status)
                : "d"(0x1F7)
            );

            if (status & 0x01)
                return;
        }

        asm volatile (
            "mov dx, 0x1F0"
            "mov esi, %[buf]"
            "mov ecx, 256"
            "rep outsw"
            :
            : [buf] "S"(buffer)
            : "ecx", "edx", "memory"
        );

        buffer += 512;
    }

    /* Wait until the drive finishes the write. */
    do {
        asm volatile (
            "in al, dx"
            : "=a"(status)
            : "d"(0x1F7)
        );
    } while (status & 0x80);
}
