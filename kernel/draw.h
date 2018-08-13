#ifndef DRAW
#define DRAW

#include <stdint.h>

void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, int color);
void draw_background(int color);

#endif
