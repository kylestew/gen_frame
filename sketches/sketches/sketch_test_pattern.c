#include "../colors.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

// Draw a 7-color pattern sketch
void drawSketch(SetPixelColorFunc setPixelColor, GetPixelColorFunc getPixelColor, int width, int height) {

    // Create a pattern using all 7 colors
    Color colors[] = {BLACK, WHITE, GREEN, BLUE, RED, YELLOW, ORANGE};
    int numColors  = 7;

    // Create horizontal stripes
    int stripeHeight = height / numColors;
    for (int y = 0; y < height; y++) {
        int colorIndex     = (y / stripeHeight) % numColors;
        Color currentColor = colors[colorIndex];

        for (int x = 0; x < width; x++) {
            setPixelColor(x, y, currentColor);
        }
    }

    // Add some geometric shapes using different colors
    int centerX = width / 2;
    int centerY = height / 2;
    int radius  = 50;

    // Draw circles in different colors
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float dx       = x - centerX;
            float dy       = y - centerY;
            float distance = sqrt(dx * dx + dy * dy);

            // Create concentric circles with different colors
            if (distance < radius) {
                setPixelColor(x, y, RED);
            } else if (distance < radius * 2) {
                setPixelColor(x, y, BLUE);
            } else if (distance < radius * 3) {
                setPixelColor(x, y, GREEN);
            }
        }
    }

    // Add a diagonal pattern in corners
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Check if in corner regions
            if ((x < 100 && y < 100) || (x > width - 100 && y > height - 100)) {
                if ((x + y) % 20 < 10) {
                    setPixelColor(x, y, YELLOW);
                } else {
                    setPixelColor(x, y, ORANGE);
                }
            }
        }
    }

    printf("7-color pattern sketch completed (%dx%d)\n", width, height);
}