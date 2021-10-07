ENAME = $(shell uname)

# set default compier commands for linux or for other system if not linux

ifeq ($(ENAME), Linux)
	CC = gcc -elf_i386
	AS = as --32
	LD = ld -m elf_i386
else
	CC=i386-elf-gcc
	AS=i386-elf-as
	LD=i386-elf-ld
endif

# set compiler flags for linker, c, cpp, assembly compiler

GFLAGS=
CCFLAGS=-m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
CCFLAGS+=-fno-builtin-function -fno-builtin
ASFLAGS=
LDFLAGS=

# set source file for bootsector

BOOTLOADER_SOURCE = src/bootloader.S

# create bootsector object file

BOOTLOADER_OBJ = $(BOOTLOADER_SOURCE:.S=.o)

# object files for kernal (commented for right now)

#KERNEL_C_FILES = $(wildcard src/*.c)

# kernel assembly files

#KERNEL_S_FILES = $(filter-out $(BOOTLOADER_SOUTCE), wildcard src/*.S)

# kernel object files

#KERNEL_OBJ = $(KERNEL_C_FILES:.c=.o) $(KERNEL_S_FILES:.S=.o)

#create the binaries and the system image
BOOTSECTOR=bootsector.bin
# KERNEL=kernel.bin
ISO=boot.iso

# all targets before iso
all: dirs bootsector #kernel

# cleans the previous compilation
clear:
	rm -f ./**/*.o
	rm -f ./*.iso
	rm -f ./**/*.bin
	rm -f ./**/*.elf

# creates dependant object files from the c files
#%.o: %.c
#	$(CC) -o $@ -c $< $(GFLAGS) $(CCFLAGS)

%.o: %.S
	$(AS) -o $@ -c $< $(GFLAGS) $(ASFLAGS)

dirs:
	mkdir -p bin

# links the bootsector and makes the first address 0x7C00
bootsector: $(BOOTLOADER_OBJ)
	$(LD) -o ./bin/$(BOOTSECTOR) $^ -Ttext 0x7C00 --oformat=binary

#links the kernel with the linker script
#kernel:
#	 $(LD) -o ./bin/$(KERNEL) $^ $(LDFLAGS) -Tsrc/link.ld

iso: dirs bootsector #kernal
	dd if=/dev/zero of=$(ISO) bs=512 count=2880
	dd if=./bin/$(BOOTSECTOR) of=$(ISO) bs=512 count=1
#    dd if=./bin/$(KERNEL) of=$(ISO) bs=512 count=2048