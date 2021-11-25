AS = nasm -f elf64

# get KERNEL assembly sources

KERNEL_SOURCE_ASM = $(wildcard protectedMode.asm)

KERNEL_OBJS = $(KERNEL_SOURCE_ASM:.asm=.o)

# do everything

all: protectedMode.o

%.o: %.asm
	$(AS) $< -o $@