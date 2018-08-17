#include "keyboard.h"
#include "../kernel/kernel.h"
#include "../cpu/ports.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../cpu/isr.h"
#include "screen.h"

#define SCANCODE_PORT 0x60 /* PIC leaves scancode in port 0x60 */
#define SCANCODE_MAX  0x39 /* Last scancode character */
#define BACKSPACE     0x0E
#define LSHIFT        0x2A
#define RSHIFT        0x36
#define ENTER         0x1C

static int is_shift = 0;
static uint8_t key_buffer_len = 0;
static char key_buffer[256];

const char *scancode_name[] = {
		"ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
		"Tab", "Q", "W", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "LCtrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "LShift", "\\",
		"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "RShift", "Keypad *", "LAlt",
		"Spacebar"
};

const char scancode_ascii[] = {
		'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\0',
		'\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\0', '\0',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'\0', '`', '\0', '\\',
		'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', '\0', '\0',
		' '
};

const char shift_scancode_ascii[] = {
		'\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\0',
		'\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\0', '\0',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', '\0', '|',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0', '\0', '\0',
		' '
};

static void keyboard_callback(registers_t regs) {
	uint8_t scancode = port_byte_in(SCANCODE_PORT);

	if (scancode == LSHIFT || scancode == RSHIFT) {
		is_shift = 1;
		/* Shift key up */
	} else if (scancode - 0x80 == LSHIFT || scancode - 0x80 == RSHIFT) {
		is_shift = 0;
	}
	if (scancode > SCANCODE_MAX) return;
	if (scancode == BACKSPACE) {
		if (key_buffer_len == 0) return;
		backspace(key_buffer);
		key_buffer_len--;
		kprint_backspace();
		return;
	} else if (scancode == ENTER) {
		kprint("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
		key_buffer_len = 0;
		return;
	} else {
		char letter = scancode_ascii[(uint32_t) scancode];
		if (is_shift == 1) letter = shift_scancode_ascii[(uint32_t) scancode];
		if (letter == '\0') return;

		/* kprint() only accepts char[] */
		char str[2] = { letter, '\0' };
		key_buffer_len++;
		append(key_buffer, letter);
		kprint(str);
	}

	UNUSED(regs);
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}
