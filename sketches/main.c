#include "colors.h"
#include "hardware/adc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Image dimensions
#define WIDTH 640
#define HEIGHT 400

// Global buffer to hold pixel data (now just 7 colors)
Color buffer[HEIGHT][WIDTH];

// Convert RGB to nearest 7-color
Color rgbToColor(unsigned char r, unsigned char g, unsigned char b) {
    // Simple mapping based on dominant color
    if (r > 200 && g > 200 && b > 200)
        return WHITE;
    if (r < 50 && g < 50 && b < 50)
        return BLACK;
    if (g > r && g > b && g > 150)
        return GREEN;
    if (b > r && b > g && b > 150)
        return BLUE;
    if (r > g && r > b && r > 150)
        return RED;
    if (r > 150 && g > 150 && b < 100)
        return YELLOW;
    if (r > 150 && g > 100 && g < 150 && b < 100)
        return ORANGE;
    return BLACK; // fallback
}

// Convert 7-color to RGB for PPM output
void colorToRGB(Color color, unsigned char *r, unsigned char *g, unsigned char *b) {
    switch (color) {
    case BLACK:
        *r = 0;
        *g = 0;
        *b = 0;
        break;
    case WHITE:
        *r = 255;
        *g = 255;
        *b = 255;
        break;
    case GREEN:
        *r = 0;
        *g = 255;
        *b = 0;
        break;
    case BLUE:
        *r = 0;
        *g = 0;
        *b = 255;
        break;
    case RED:
        *r = 255;
        *g = 0;
        *b = 0;
        break;
    case YELLOW:
        *r = 255;
        *g = 255;
        *b = 0;
        break;
    case ORANGE:
        *r = 255;
        *g = 128;
        *b = 0;
        break;
    case CLEAN:
        *r = 255;
        *g = 255;
        *b = 255;
        break; // same as white
    default:
        *r = 0;
        *g = 0;
        *b = 0;
        break;
    }
}

// setPixel function that writes to the buffer (accepts RGB, converts to 7-color)
void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        buffer[y][x] = rgbToColor(r, g, b);
    }
}

// setPixelColor function that directly sets 7-color
void setPixelColor(int x, int y, Color color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        buffer[y][x] = color;
    }
}

// getPixel function that reads from the buffer
void getPixel(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        colorToRGB(buffer[y][x], r, g, b);
    } else {
        *r = *g = *b = 0;
    }
}

// getPixelColor function that directly gets 7-color
Color getPixelColor(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        return buffer[y][x];
    }
    return BLACK;
}

// Function pointer types for RGB (kept for compatibility)
typedef void (*SetPixelFunc)(int x, int y, unsigned char r, unsigned char g, unsigned char b);
typedef void (*GetPixelFunc)(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b);

// External sketch function declaration
extern void drawSketch(int width, int height, SetPixelColorFunc setPixelColor, GetPixelColorFunc getPixelColor);

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
            unsigned char r, g, b;
            colorToRGB(buffer[y][x], &r, &g, &b);
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Image written to %s\n", filename);
}

int main() {
    // Initialize buffer to black
    memset(buffer, 0, sizeof(buffer));

    // seed random numbers
    adc_init();
    adc_gpio_init(26); // Or leave pin floating (GPIO26 is ADC0)
    adc_select_input(0);
    uint16_t noise = adc_read();
    srand(noise);

    // Call the sketch function with our indexed color functions
    drawSketch(WIDTH, HEIGHT, setPixelColor, getPixelColor);

    // Write the image to disk
    writePPM("output.ppm", WIDTH, HEIGHT);

    return 0;
}
