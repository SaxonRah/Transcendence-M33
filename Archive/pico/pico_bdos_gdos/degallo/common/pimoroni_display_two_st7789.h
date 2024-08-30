#ifndef _PIMORONI_DISPLAY_TWO_ST7789_H_
#define _PIMORONI_DISPLAY_TWO_ST7789_H_

#include "hardware/spi.h"

struct st7789_config {
    spi_inst_t* spi;
    uint gpio_din;
    uint gpio_clk;
    int gpio_cs;
    uint gpio_dc;
    uint gpio_rst;
    uint gpio_bl;
};

void pimoroni_display_two_st7789_init(const struct st7789_config* config, uint16_t width, uint16_t height);
void pimoroni_display_two_st7789_write(const void* data, size_t len);
void pimoroni_display_two_st7789_put(uint16_t pixel);
void pimoroni_display_two_st7789_fill(uint16_t pixel);
void pimoroni_display_two_st7789_set_cursor(uint16_t x, uint16_t y);
void pimoroni_display_two_st7789_vertical_scroll(uint16_t row);

#endif