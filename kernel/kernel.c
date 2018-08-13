#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "draw.h"
#include <stdint.h>

void draw_task_bar() {
	draw_rect(0,200-10,320,10,0x1c);
}

void main() {
	isr_install();
	draw_background(0x35);
	draw_rect(0,10,5,10, 2);
	draw_task_bar();
}
