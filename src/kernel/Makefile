AS = nasm -f elf32

# get KERNEL assembly sources

KERNEL_SOURCE_ASM = $(wildcard kernel.asm)

# get kernel c sources

#KERNEL_SOURCE_C = $(wildcard *.c)

KERNEL_OBJS = $(KERNEL_SOURCE_ASM:.asm=.o) #$(KERNEL_SOURCE_C:.c=.o)

# do everything

all: kernel.o

%.o: %.asm
	$(AS) $< -o $@