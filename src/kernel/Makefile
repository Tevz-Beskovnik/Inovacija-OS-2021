
OSNAME = sfsOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = gcc
GPP = g++
LD = ld

VMEM = 256M

CFLAGS = -ffreestanding -fshort-wchar
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

IMG = sfsOS.img
SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

clear:
	rm ./lib/*.o
	rm ./bin/*.img
	rm ./bin/*.elf

kernel: $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(GPP) $(CFLAGS) -c $^ -o $@ -fPIC
	
link:
	@ echo !==== LINKING
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS) -shared -fstack-protector

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(IMG) bs=512 count=93750
	mformat -i $(BUILDDIR)/$(IMG) -f 1440 ::
	mmd -i $(BUILDDIR)/$(IMG) ::/EFI
	mmd -i $(BUILDDIR)/$(IMG) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(IMG) $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(IMG) startup.nsh ::
	mcopy -i $(BUILDDIR)/$(IMG) $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(IMG) $(BUILDDIR)/zap-light16.psf ::

img:
	qemu-system-x86_64 -drive file=$(BUILDDIR)/$(IMG) -m ${VMEM} -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none

build: kernel link buildimg

all: kernel link buildimg img