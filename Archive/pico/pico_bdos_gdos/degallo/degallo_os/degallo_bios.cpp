#include "degallo_bios.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "../common/Adafruit_ST7789.h"
#include "../common/SD.h"
#include <string.h>

#define TFT_CS    17
#define TFT_DC    16
#define TFT_SCLK  18
#define TFT_MOSI  19
#define TFT_RST   -1

#define SD_CS     22
#define SD_SCK    18
#define SD_MOSI   19
#define SD_MISO   16

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void bios_init() {
    // Initialize display
    tft.init(240, 320);
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);

    // Initialize SD card
    if (!SD.begin(SD_CS)) {
        // Handle SD initialization failure
    }
}

void bios_write_display(const char *message) {
    tft.print(message);
}

void bios_read_sd(const char *filename, uint8_t *buffer, size_t size) {
    File file = SD.open(filename, FILE_READ);
    if (file) {
        file.read(buffer, size);
        file.close();
    }
}

void bios_write_sd(const char *filename, const uint8_t *data, size_t size) {
    File file = SD.open(filename, FILE_WRITE);
    if (file) {
        file.write(data, size);
        file.close();
    }
}
