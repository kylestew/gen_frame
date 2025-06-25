#include "colors.h"
#include "lib/uc8159.hpp"
#include "pico/stdlib.h"
#include "sketch.c"

#include <cstring> // memory allocation

/*
Hardware module: if you want to work with buttons and examples for sleep/wake up
https://github.com/pimoroni/pimoroni-pico/blob/main/libraries/inky_frame/inky_frame.cpp
*/

// Inky Framce 4.0 - Pico W pinout
enum Pin {
    HOLD_VSYS_EN = 2,
    I2C_INT      = 3,
    I2C_SDA      = 4,
    I2C_SCL      = 5,
    STATUS_LED   = 6,
    SR_CLOCK     = 8,
    SR_LATCH     = 9,
    SR_OUT       = 10,
    MISO         = 16,
    EINK_CS      = 17,
    CLK          = 18,
    MOSI         = 19,
    SD_DAT0      = 19,
    SD_DAT1      = 20,
    SD_DAT2      = 21,
    SD_DAT3      = 22,
    SD_CS        = 22,
    ADC0         = 26,
    EINK_RESET   = 27,
    EINK_DC      = 28
};

#define WIDTH 640
#define HEIGHT 400
const size_t BUFFER_SIZE = WIDTH * HEIGHT / 2;

UC8159 display(WIDTH, HEIGHT, UC8159::ROTATE_0, {spi0, EINK_CS, CLK, MOSI, PIN_UNUSED, EINK_DC, PIN_UNUSED});
uint8_t framebuffer[BUFFER_SIZE];

void clear_framebuffer_3bit(uint8_t color) {
    uint8_t kpixel = color & 0x07;            // Ensure 3-bit color
    uint8_t packed = (kpixel << 4) | kpixel;  // Pack as: [b2 b1 b0 0 a2 a1 a0]
    memset(framebuffer, packed, BUFFER_SIZE); // Fill framebuffer
}

void write_pixel(uint8_t *buffer, int width, int x, int y, uint8_t color) {
    int index   = (y * width + x) / 2; // 2 pixels per byte
    bool is_low = (x % 2) == 0;

    uint8_t orig = buffer[index];
    if (is_low) {
        // Lower nibble (bits 2:0)
        orig = (orig & 0xF0) | (color & 0x07);
    } else {
        // Upper nibble (bits 6:4)
        orig = (orig & 0x0F) | ((color & 0x07) << 4);
    }

    buffer[index] = orig;
}

uint8_t read_pixel(uint8_t *buffer, int width, int x, int y) {
    int index   = (y * width + x) / 2; // 2 pixels per byte
    bool is_low = (x % 2) == 0;

    uint8_t orig = buffer[index];
    if (is_low) {
        // Lower nibble (bits 2:0)
        return orig & 0x07;
    } else {
        // Upper nibble (bits 6:4)
        return (orig >> 4) & 0x07;
    }
}

// Indexed color set/get functions for the sketch system
void setPixelColor(int x, int y, Color color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        write_pixel(framebuffer, WIDTH, x, y, (uint8_t) color);
    }
}

Color getPixelColor(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        return (Color) read_pixel(framebuffer, WIDTH, x, y);
    }
    return BLACK;
}

int main() {
    stdio_init_all();
    sleep_ms(500);

    // status LED
    gpio_init(STATUS_LED);
    gpio_set_function(STATUS_LED, GPIO_FUNC_SIO);
    gpio_set_dir(STATUS_LED, GPIO_OUT);

    while (true) {
        gpio_put(STATUS_LED, 1);

        // clear display buffer
        clear_framebuffer_3bit(7); // clean color

        // draw using the sketch system
        drawSketch(setPixelColor, getPixelColor, WIDTH, HEIGHT);

        display.update(framebuffer, BUFFER_SIZE);

        sleep_ms(STATUS_LED);
        gpio_put(STATUS_LED, 0);

        sleep_ms(100000);
    }
}