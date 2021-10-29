AS = nasm -f elf32 

# bootloader sources

BOOTLOADER_SOURCE = $(wildcard bootloader.asm protectedMode.asm)

# bootloader objects

BOOTLAODER_OBJ = $(BOOTLOADER_SOURCE:.asm=.o)

# convert assembly file into object file

all: bootloader.o protectedMode.o

%.o: %.asm
	$(AS) $< -o $@
