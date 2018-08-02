
/*
 * Read a byte from the specified port.
 */
unsigned char port_byte_in (unsigned short port) {
	unsigned char result;
	/*
	 * Inline assembly syntax.
	 * Notice that source and destination registers
	 * are swapped, because GCC uses GAS syntax, not
	 * NASM.
	 *
	 * "=a" (result) ==> set (=) the variable (result) to the value of register eax
	 * "d"  (port)   ==> map the C variable (port) into the edx register
	 *
	 * Inputs & outputs separated by a colon.
	 */
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
}

void port_byte_out (unsigned short port, unsigned char data) {
	/*
	 * Note how both registers are mapped to C variables
	 * and nothing is returned -- so no "=" sign.
	 * We see a comma because there are two variables in the
	 * input area, and none in the "return" area.
	 */
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_word_out (unsigned short port, unsigned short data) {
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
