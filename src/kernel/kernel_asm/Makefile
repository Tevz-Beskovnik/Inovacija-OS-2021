AS = nasm -f elf64

# get KERNEL assembly sources

KERNEL_SOURCE_ASM = $(wildcard protectedMode.asm binaries.asm)

# get kernel c sources

#KERNEL_SOURCE_C = $(wildcard *.c)

KERNEL_OBJS = $(KERNEL_SOURCE_ASM:.asm=.o) #$(KERNEL_SOURCE_C:.c=.o)

# do everything

all: protectedMode.o binaries.o

%.o: %.asm
	$(AS) $< -o $@