# build and run
make iso
qemu-system-i386 -drive format=raw,file=boot.iso -d cpu_reset -monitor stdio