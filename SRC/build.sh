echo "=== Building kernel entry ==="

nasm -f elf32 boot.asm -o boot.o

echo "=== Building GDT ==="

nasm -f elf32 gdt.asm -o gdt.o

echo "=== Building IDT assembly ==="

nasm -f elf32 idt.asm -o idtasm.o

echo "=== Building kernel C files ==="

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c kernel.c \
    -o kernel.o

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c vga.c \
    -o vga.o

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c idt.c \
    -o idt.o

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c int0x60.c \
    -o int0x60.o

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c memory.c \
    -o memory.o

gcc -m32 \
    -ffreestanding \
    -fno-pie \
    -masm=intel \
    -c ata.c \
    -o ata.o

echo "=== Linking kernel ==="

ld -m elf_i386 \
    -T linker.ld \
    -o kernel.elf \
    boot.o \
    kernel.o \
    vga.o \
    gdt.o \
    idtasm.o \
    idt.o \
    int0x60.o \
    memory.o \
    ata.o

echo "=== Creating HDD image ==="

rm -f disk.img

dd if=/dev/zero \
    of=disk.img \
    bs=1M \
    count=128 \
    status=none

echo "=== Creating MBR partition table ==="

parted -s disk.img mklabel msdos

parted -s disk.img \
    mkpart primary fat16 1MiB 100%

parted -s disk.img \
    set 1 boot on

echo "=== Connecting image to loop device ==="

LOOPDEV=$(sudo losetup --find --show --partscan disk.img)

echo "Loop device: $LOOPDEV"

sleep 1

echo "=== Formatting FAT16 ==="

sudo mkfs.fat -F 16 "${LOOPDEV}p1"

echo "=== Installing GRUB ==="

mkdir -p mnt

sudo mount "${LOOPDEV}p1" mnt

sudo grub-install \
    --target=i386-pc \
    --boot-directory="$PWD/mnt/boot" \
    --modules="part_msdos fat normal multiboot" \
    "$LOOPDEV"

echo "=== Installing kernel ==="

sudo cp kernel.elf mnt/kernel.elf

echo "=== Creating GRUB configuration ==="

sudo mkdir -p mnt/boot/grub

sudo tee mnt/boot/grub/grub.cfg > /dev/null << 'EOF'
set timeout=0
set default=0

menuentry "MyOS" {
    multiboot /kernel.elf
    boot
}
EOF

sync

echo "=== Unmounting ==="

sudo umount mnt

sudo losetup -d "$LOOPDEV"

echo "=== Checking partition table ==="

fdisk -l disk.img

echo "=== Starting QEMU ==="

qemu-system-i386 -drive format=raw,file=disk.img
