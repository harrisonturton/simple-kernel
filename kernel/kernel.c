#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void main() {
	isr_install();
	irq_install();
}


void user_input(uint8_t *input) {
	kprint(input);
}
