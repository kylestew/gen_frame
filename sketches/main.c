#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Image dimensions
#define WIDTH 800
#define HEIGHT 600

// RGB color structure
typedef struct {
    unsigned char r, g, b;
} Color;

// Global buffer to hold pixel data
Color buffer[HEIGHT][WIDTH];

// setPixel function that writes to the buffer
void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        buffer[y][x].r = r;
        buffer[y][x].g = g;
        buffer[y][x].b = b;
    }
}

// Function pointer type for setPixel
typedef void (*SetPixelFunc)(int x, int y, unsigned char r, unsigned char g, unsigned char b);

// Function pointer type for sketch
typedef void (*SketchFunc)(SetPixelFunc setPixel, int width, int height);

// External sketch function declaration
extern void drawSketch(SetPixelFunc setPixel, int width, int height);

// Write PPM image to file
void writePPM(const char *filename, int width, int height) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        exit(1);
    }

    // Write PPM header
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    // Write pixel data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fprintf(file, "%d %d %d ", buffer[y][x].r, buffer[y][x].g, buffer[y][x].b);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Image written to %s\n", filename);
}

int main() {
    // Initialize buffer to black
    memset(buffer, 0, sizeof(buffer));

    // Call the sketch function with our setPixel function
    drawSketch(setPixel, WIDTH, HEIGHT);

    // Write the image to disk
    writePPM("output.ppm", WIDTH, HEIGHT);

    return 0;
}