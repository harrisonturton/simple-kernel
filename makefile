
# Default build target
all: os-image

# --------- Helpful Commands ----------

# Clear all generated files
clean:
	rm -fr *.bin *.dis *.o os-image *.map
	rm -r build/*.o build/*.bin

# Disassemble kernel for debugging
kernel.dis: build/kernel.bin
	ndisasm -b 32 $< > $@

# Run qemu to simulate booting
run: all
	echo "Running..."
	qemu-system-i386 -fda os-image

# --------- Build procedures ----------

# The actual disk image that our computer loads.
# A combo of the bootsector and kernel.
os-image: build/boot.bin build/kernel.bin
	cat $^ > os-image

# Build the kernel binary from the two main obj files:
# 	- kernel_entry, which jumps to main() in the kernel
# 	- kernel.o, the compiled C kernel
build/kernel.bin: build/kernel_entry.o build/kernel.o
	ld -m elf_i386 -s -o $@ -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
build/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -c $< -o $@

# Build kernel entry object file
build/kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf -o $@

# Assemble the boot sector to machine code
build/boot.bin: boot/boot.asm
	nasm $< -f bin -I "boot/" -o $@
