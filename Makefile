ENAME = $(shell uname)

# set default compier commands for linux or for other system if not linux

ifeq ($(ENAME), Linux)
	CC = gcc -elf_i386
	AS = nasm -f elf32
	LD = ld -m elf_i386
	MAKE = make
else
	CC=i386-elf-gcc
	AS=i386-elf-as
	LD=i386-elf-ld
	MAKE = make
endif

# set compiler flags for linker, c, cpp, assembly compiler

GFLAGS=
CCFLAGS=-m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
CCFLAGS+=-fno-builtin-function -fno-builtin
ASFLAGS=
LDFLAGS=

# makefile location of the bootloader

BOOTLOADER_MAKE = ./src/bootloader

# location of the debug kernel

KERNEL_DEBUG_MAKE = ./src/kernel

# create bootsector object file made in BOOTLOADER_MAKE

BOOTLOADER_OBJ = src/bootloader/bootloader.o

BOOTLOADER_EXT_OBJ = src/bootloader/protectedMode.o

# object files for kernal (commented for right now)

#KERNEL_C_FILES = $(wildcard src/*.c)

# kernel assembly files

#KERNEL_S_FILES = $(filter-out $(BOOTLOADER_SOUTCE), wildcard src/*.S)

# kernel object files

#KERNEL_DEBUG_DEBUG = src/kernel/kernel.o

#KERNEL_OBJ = $(KERNEL_C_FILES:.c=.o) $(KERNEL_S_FILES:.S=.o)

#create the binaries and the system image
BOOTSECTOR=bootsector.bin
BOOTSECTOR_EXT=bootsector_ext.bin
#KERNEL=kernel.bin
ISO=boot.iso

# all targets before iso
all: clear dirs objects bootsector bootsector_ext #kernel

# cleans the previous compilation
clear:
	rm -f ./**/*.o
	rm -f ./**/**/*.o
	rm -f ./*.iso
	rm -f ./**/*.bin
	rm -f ./**/*.elf

# creates dependant object files from the c files
#%.o: %.c
#	$(CC) -o $@ -c $< $(GFLAGS) $(CCFLAGS)

#%.o: %.asm
#	$(AS) $< -o $@x
objects:
	$(MAKE) -C $(BOOTLOADER_MAKE)
#	$(MAKE) -C $(KERNEL_DEBUG_MAKE)

dirs:
	mkdir -p bin

# link the bootsector
bootsector: $(BOOTLOADER_OBJ)
	$(LD) -o ./bin/$(BOOTSECTOR) $^ -Ttext 0x7C00 --oformat=binary

bootsector_ext: $(BOOTLOADER_EXT_OBJ)
	$(LD) -o ./bin/$(BOOTSECTOR_EXT) $^ -Ttext 0x7E00 --oformat=binary

# links the kernel with the linker script
#kernel: $(KERNEL_DEBUG_DEBUG)
#	$(LD) -o ./bin/$(KERNEL) $^ $(LDFLAGS) -Tsrc/kernel/link.ld

# copy all of the contetnts to the iso file
iso: clear dirs objects bootsector bootsector_ext #kernel
#    dd if=/dev/zero of=$(ISO) bs=512 count=2880
	dd if=/dev/zero of=$(ISO) bs=512 count=5
	dd if=./bin/$(BOOTSECTOR) of=$(ISO) bs=512 seek=0 count=1
	dd if=./bin/$(BOOTSECTOR_EXT) of=$(ISO) bs=512 seek=1 count=4
#	dd if=./bin/$(KERNEL) of=$(ISO) bs=512 seek=1 count=4