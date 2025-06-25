#include <math.h>
#include <stdio.h>

// Function pointer type for setPixel
typedef void (*SetPixelFunc)(int x, int y, unsigned char r, unsigned char g, unsigned char b);

// Draw a beautiful gradient sketch
void drawSketch(SetPixelFunc setPixel, int width, int height) {
    // Create a radial gradient from center
    int centerX       = width / 2;
    int centerY       = height / 2;
    float maxDistance = sqrt(centerX * centerX + centerY * centerY);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate distance from center
            float dx       = x - centerX;
            float dy       = y - centerY;
            float distance = sqrt(dx * dx + dy * dy);

            // Normalize distance to 0-1 range
            float normalizedDistance = distance / maxDistance;

            // Create gradient colors
            unsigned char r = (unsigned char) (255 * (1.0 - normalizedDistance));
            unsigned char g = (unsigned char) (255 * normalizedDistance);
            unsigned char b = (unsigned char) (128 + 127 * sin(normalizedDistance * 3.14159));

            // Set the pixel
            setPixel(x, y, r, g, b);
        }
    }

    printf("Gradient sketch completed (%dx%d)\n", width, height);
}