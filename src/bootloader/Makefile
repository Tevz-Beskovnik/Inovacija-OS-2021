AS = nasm -f elf32 

# bootloader sources

BOOTLOADER_SOURCE = $(wildcard bootloader.asm extendedSpace.asm)

# bootloader objects

BOOTLAODER_OBJ = $(BOOTLOADER_SOURCE:.asm=.o)

# convert assembly file into object file

all: bootloader.o extendedSpace.o

%.o: %.asm
	$(AS) $< -o $@
