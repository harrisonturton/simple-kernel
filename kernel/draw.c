#include "draw.h"

#define VIDEO_MEMORY  0xA0000	/* Memory location of VGA table  */
#define SCREEN_WIDTH  320		/* Width  in pixels of mode 0x13 */
#define SCREEN_HEIGHT 200		/* Height in pixels of mode 0x13 */
#define MEM_WIDTH     80        /* Width in memory locations, i.e. SCREEN_WIDTH / 8 */

void draw_pixel(int x, int y, uint32_t color) {
	intptr_t *vidmem = (intptr_t *) VIDEO_MEMORY;
	int memory_offset = (y * MEM_WIDTH) + (x / 4);
	uint32_t current_color = vidmem[memory_offset];
	//vidmem[memory_offset] = 0x00010203;
	/* Shift color to proper location */
	int offset = (x % 4) * 8;
	color = color << offset;
	/* Clear previous color */
	uint32_t mask = (uint32_t) 0xff << offset;
	current_color = current_color & ~mask;
	/* Add new color */
	current_color = current_color | color;
	vidmem[memory_offset] = current_color;
}

void draw_rect(int x, int y, int width, int height, int color) {
	int i, j;
	for (i = x; i < width + x; i++) {
		for (j = y; j < height + y; j++) {
			draw_pixel(i, j, color);
		}
	}
}

void draw_background(int color) {
	draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}
