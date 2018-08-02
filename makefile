
make: boot.asm kernel.c
	nasm -f bin boot.asm -o build/boot.bin -Ox
	gcc -ffreestanding -c kernel.c -o build/kernel.o
	ld -o build/kernel.bin -Ttext 0x1000 build/kernel.o --oformat binary
	cat build/boot.bin build/kernel.bin > build/os-image
