ENAME = $(shell uname)

# set default compier commands for linux or for other system if not linux

ifeq ($(ENAME), Linux)
	CC = gcc -elf_x86_64
	CXX = g++ -elf_x86_64
	LD = ld
	MAKE = make
else
	CC=i386-elf-gcc
	LD=i386-elf-ld
	MAKE = make
endif

# set compiler flags for linker, c, cpp, assembly compiler

GFLAGS=
CCFLAGS= -m64 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing -mno-red-zone -march=x86-64
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
CCFLAGS+=-fno-builtin-function -fno-builtin
ASFLAGS=
LDFLAGS=

# makefile location of the bootloader

BOOTLOADER_MAKE = ./src/bootloader

# location of the debug kernel

KERNEL_MAKE = ./src/kernel/kernel_asm

# create bootsector object file made in BOOTLOADER_MAKE

BOOTLOADER_OBJ = src/bootloader/bootloader.o

# extended boot enables long mode and 32bit real mode

BOOTLOADER_EXT_OBJ = src/kernel/kernel_asm/protectedMode.o

# external assembly objects

KERNEL_ASM_OBJ = src/kernel/kernel_asm/binaries.o

# object files for kernal (commented for right now)

KERNEL_CPP_FILES = $(wildcard src/kernel/*.c)

# kernel assembly files

#KERNEL_S_FILES = $(filter-out $(BOOTLOADER_SOUTCE), wildcard src/*.S)

# kernel object files

#KERNEL_DEBUG_DEBUG = src/kernel/kernel.o

KERNEL_OBJ = $(BOOTLOADER_EXT_OBJ) $(KERNEL_CPP_FILES:.c=.o) $(KERNEL_ASM_OBJ)

#create the binaries and the system image
BOOTSECTOR=bootsector.bin
KERNEL=kernel.bin
ISO=boot.iso

# all targets before iso
all: clear dirs objects bootsector kernel

# cleans the previous compilation
clear:
	rm -f ./**/*.o
	rm -f ./**/**/*.o
	rm -f ./**/**/**/*.o
	rm -f ./*.iso
	rm -f ./**/*.bin
	rm -f ./**/*.elf

# creates dependant object files from the c files
%.o: %.c
	$(CC) -o $@ -c $< $(GFLAGS) $(CCFLAGS)

#%.o: %.asm
#	$(AS) $< -o $@x
objects:
	$(MAKE) -C $(BOOTLOADER_MAKE)
	$(MAKE) -C $(KERNEL_MAKE)

dirs:
	mkdir -p bin

# link the bootsector
bootsector: $(BOOTLOADER_OBJ)
	$(LD) -m elf_i386 -o ./bin/$(BOOTSECTOR) $^ -Ttext 0x7C00 --oformat=binary

#bootsector_ext: $(BOOTLOADER_EXT_OBJ)
#	$(LD) -o ./bin/$(KERNEL) $^ -Ttext 0x7E00 --oformat=binary

# links the kernel with the linker script
kernel: $(KERNEL_OBJ)
	$(LD) -m elf_x86_64 -o ./bin/$(KERNEL) $^ -Tsrc/kernel/link.ld

# copy all of the contetnts to the iso file
iso: clear dirs objects bootsector kernel
#    dd if=/dev/zero of=$(ISO) bs=512 count=2880
	dd if=/dev/zero of=$(ISO) bs=512 count=2880
	dd if=./bin/$(BOOTSECTOR) of=$(ISO) bs=512 seek=0 count=1
	dd if=./bin/$(KERNEL) of=$(ISO) bs=512 seek=1 count=16