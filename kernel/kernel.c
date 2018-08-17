#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void main() {
	isr_install();
	irq_install();

	clear_screen();
	kprint(" > ");
}


void user_input(uint8_t *input) {
	if (strcmp(input, "end") == 0) {
		kprint("Stopping the CPU...\n");
		asm volatile("hlt");
	}
	if (strcmp(input, "clear") == 0) {
		clear_screen();
		kprint(" > ");
		return;
	}
	kprint("$ ");
	kprint(input);
	kprint("\n > ");
}
