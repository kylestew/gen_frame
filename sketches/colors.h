#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

// 7-color display enum
typedef enum { BLACK = 0, WHITE = 1, GREEN = 2, BLUE = 3, RED = 4, YELLOW = 5, ORANGE = 6, CLEAN = 7 } Color;

// Function pointer types for indexed colors
typedef void (*SetPixelColorFunc)(int x, int y, Color color);
typedef Color (*GetPixelColorFunc)(int x, int y);

#endif // COLORS_H