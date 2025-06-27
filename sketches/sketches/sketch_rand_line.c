#include "../colors.h"
#include "rendering.h"

#include <stdlib.h>
#include <time.h>

void drawSketch(int width, int height, SetPixelColorFunc setPixelColor, GetPixelColorFunc getPixelColor) {
    Color colors[] = {BLACK, WHITE, GREEN, BLUE, RED, YELLOW, ORANGE};

    srand(time(NULL)); // Use current time as seed

    int x0 = rand() % width;
    int x1 = rand() % width;
    int y0 = rand() % height;
    int y1 = rand() % height;

    draw_line(x0, y0, x1, y1, colors[1], setPixelColor);
}
