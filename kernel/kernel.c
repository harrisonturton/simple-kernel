#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void main() {
	isr_install();
	irq_install();

	char* str;
	int_to_ascii(sizeof(int), str);
	kprint(str);
}
