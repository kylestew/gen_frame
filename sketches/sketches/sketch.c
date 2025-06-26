#include "../colors.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color, SetPixelColorFunc setPixelColor) {
    // Bresenham - incremental error algorithm
    // determines which pixel is closest to the ideal line between two points, and
    // steps one pixel at a time in either the x or y direction
    bool steep = abs(x1 - x0) < abs(y1 - y0);
    if (steep) { // if line is steep, we transpose it
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if (x0 > x1) { // make it left-to-right
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);

    int err   = 0;
    int ystep = (y0 < y1) ? 1 : -1;
    int y     = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) { // if transposed, de-transpose
            setPixelColor(y, x, color);
        } else {
            setPixelColor(x, y, color);
        }

        err += 2 * dy;
        if (err > dx) {
            y += ystep;
            err -= 2 * dx;
        }
    }
}

void drawSketch(int width, int height, SetPixelColorFunc setPixelColor, GetPixelColorFunc getPixelColor) {
    Color colors[] = {BLACK, WHITE, GREEN, BLUE, RED, YELLOW, ORANGE};

    srand(time(NULL)); // Use current time as seed

    int x0 = rand() % width;
    int x1 = rand() % width;
    int y0 = rand() % height;
    int y1 = rand() % height;

    printf("Screen dimensions: %d x %d\n", width, height);
    printf("Line coordinates: (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);

    draw_line(x0, y0, x1, y1, colors[1], setPixelColor);
}