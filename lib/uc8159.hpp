#pragma once

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include <initializer_list>

/*
https://github.com/pimoroni/pimoroni-pico/blob/main/drivers/uc8159/uc8159.hpp
*/

#define PIN_UNUSED 0xff

class UC8159 {

  public:
    enum Rotation { ROTATE_0 = 0, ROTATE_90 = 90, ROTATE_180 = 180, ROTATE_270 = 270 };

    struct SPIPins {
        spi_inst_t *spi;
        uint cs;
        uint sck;
        uint mosi;
        uint miso;
        uint dc;
        uint bl;
    };

    enum colour : uint8_t {
        BLACK  = 0, //
        WHITE  = 1,
        GREEN  = 2,
        BLUE   = 3,
        RED    = 4,
        YELLOW = 5,
        ORANGE = 6,
        CLEAN  = 7
    };

    uint16_t width;
    uint16_t height;
    Rotation rotation;

    UC8159(uint16_t width, uint16_t height, Rotation rotation, SPIPins pins, uint busy = PIN_UNUSED, uint reset = 27)
        : width(width), height(height), rotation(rotation), //
          spi(pins.spi),                                    //
          CS(pins.cs), DC(pins.dc), SCK(pins.sck), MOSI(pins.mosi), BUSY(busy), RESET(reset) {
        init();
    }

    void reset();

    // TODO: what format is buffer expected in? Can we take in 8bit per pixel format?
    void update(const uint8_t *buffer, size_t buffer_length);

  private:
    spi_inst_t *spi = spi0;

    // interface pins with our standard defaults where appropriate
    uint CS;
    uint DC;
    uint SCK;
    uint MOSI;
    uint BUSY;
    uint RESET;

    absolute_time_t timeout;
    bool blocking = true;

    void init();
    void setup();

    bool is_busy();
    void busy_wait(uint minimum_wait_ms = 0);

    void command(uint8_t reg, size_t len, const uint8_t *data);
    void command(uint8_t reg, std::initializer_list<uint8_t> values);
    void command(uint8_t reg, const uint8_t data) { command(reg, 0, &data); };
    void command(uint8_t reg) { command(reg, 0, nullptr); };
};