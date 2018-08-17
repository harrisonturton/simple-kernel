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
#define ENTER         0x1C

static char key_buffer[256];

const char *scancode_name[] = {
		"ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
		"Tab", "Q", "W", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "LCtrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "LShift", "\\",
		"Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "RShift", "Keypad *", "LAlt",
		"Spacebar"
};

const char scancode_ascii[] = {
		'_', '_', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '_',
		'_', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '_', '_',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '_', '\\',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '_', '_', '_',
		' '
};

static void keyboard_callback(registers_t regs) {
	uint8_t scancode = port_byte_in(SCANCODE_PORT);

	if (scancode > SCANCODE_MAX) return;
	if (scancode == BACKSPACE) {
		kprint_backspace();
		return;
	} else if (scancode == ENTER) {
		kprint("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
		return;
	} else {
		char letter = scancode_ascii[(uint32_t) scancode];
		/* kprint() only accepts char[] */
		char str[2] = { letter, '\0' };
		append(key_buffer, letter);
		kprint(str);
	}

	UNUSED(regs);
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}

/*
static void keyboard_callback(registers_t regs) {
	/* PIC leaves us the scancode in port 0x60
	uint8_t scancode = port_byte_in(0x60);
	char *sc_ascii;
	print_letter(scancode);
}
void print_letter(uint8_t scancode) {
		default:
			/* Unknown key down *
			/* Haven't handled previously *
			if (scancode < 0x7F) {
				kprint("Unknown key down");
				return;
			}

			/* Known key up *
			/* Key up is "keydown + 0x80" *
			if (scancode <= 0x39 + 0x80) {
				/* Do nothing */
				/* Key released is at "scancode - 0x80"
				return;
			}

			/* Unknown key up
			// No nothing
	}
}*/
