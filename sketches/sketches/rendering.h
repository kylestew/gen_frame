#ifndef RENDERING_H
#define RENDERING_H

#include "../colors.h"
#include <stdint.h>

void draw_line(int x0, int y0, int x1, int y1, uint8_t color, SetPixelColorFunc setPixelColor);

#endif
