#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/rtc.h"

// Include necessary libraries
#include "pimoroni_display_two_st7789.h"
#include "pimoroniTrackball.h"
#include "RTClib.h"

// I2C addresses
#define I2C_MULTIPLEXER 0x70
#define I2C_RTC 0x68
#define I2C_TB 0x0A

// SPI and GPIO definitions
#define TFT_DC 16
#define TFT_CS 17
#define TFT_SCLK 18
#define TFT_MOSI 19
#define TFT_RST -1
#define TFT_BL 20

#define SD_DETECT 15
#define SD_MISO 16
#define SD_CS 22
#define SD_SCK 18
#define SD_MOSI 19

// Global variables
bool RTC_INIT = false;
bool SD_INIT = false;
bool TB_INIT = false;
bool SCREEN_INIT = false;

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
PimoroniTrackball trackball;
RTC_PCF8523 rtc;

void pca_select(uint8_t i) {
    if (i > 3) return;
    uint8_t command = (1 << i);
    i2c_write_blocking(i2c_default, I2C_MULTIPLEXER, &command, 1, false);
}

void debug_msg(const char* debug_message) {
    // Print to Serial
    printf("%s\n", debug_message);

    // Print to Screen
    if (SCREEN_INIT) {
        tft.setCursor(0, 0);
        tft.print(debug_message);
    }
}

void cycleTrackballColors() {
    if (TB_INIT) {
        static float hue = 0;
        hue += 0.5;  // Adjust this value to change the speed of the transition
        if (hue >= 360) hue = 0;

        // Convert HSV to RGB
        float s = 1.0, v = 1.0;
        int i = (int)(hue / 60) % 6;
        float f = (hue / 60) - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        uint8_t r, g, b;
        switch (i) {
            case 0: r = v * 255; g = t * 255; b = p * 255; break;
            case 1: r = q * 255; g = v * 255; b = p * 255; break;
            case 2: r = p * 255; g = v * 255; b = t * 255; break;
            case 3: r = p * 255; g = q * 255; b = v * 255; break;
            case 4: r = t * 255; g = p * 255; b = v * 255; break;
            case 5: r = v * 255; g = p * 255; b = q * 255; break;
        }

        trackball.setRGBW(r, g, b, 255);
        sleep_ms(10);  // Adjust delay for speed of color change
    }
}

void setup() {
    // Initialize Serial for debugging
    stdio_init_all();
    debug_msg("Serial initialized.");

    // Screen Setup
    tft.init(240, 320);
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);
    SCREEN_INIT = true;
    debug_msg("Pico - De Gallo OS - ver 0.0.0");

    // Initialize I2C
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
    debug_msg("I2C Initialized.");

    // Ensure the SPI pinout the SD card is connected to is configured properly
    spi_init(spi0, 1000 * 1000);
    gpio_set_function(SD_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SD_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SD_SCK, GPIO_FUNC_SPI);
    gpio_set_function(SD_CS, GPIO_FUNC_SIO);
    gpio_pull_up(SD_DETECT);

    gpio_init(SD_CS);
    gpio_set_dir(SD_CS, GPIO_OUT);
    gpio_put(SD_CS, 1); // Deactivate SD card CS
    gpio_put(TFT_CS, 1); // Deactivate Screen CS

    // Check if SD card is inserted
    if (!gpio_get(SD_DETECT)) {
        debug_msg("SD card detected.");
        debug_msg("Attempting SD card initialization...");

        // Attempt to initialize SD card
        if (!SD.begin(SD_CS)) {
            SD_INIT = false;
            debug_msg("SD initialization failed!");
        } else {
            SD_INIT = true;
            debug_msg("SD initialization done.");
        }
    } else {
        SD_INIT = false;
        debug_msg("No SD card detected!");
    }

    // Initialize the trackball
    pca_select(1);
    trackball.begin();
    if (trackball.isConnected()) {
        TB_INIT = true;
        trackball.setRGBW(255, 255, 255, 255);
        cycleTrackballColors();
        Mouse.begin();
        debug_msg("Trackball initialized.");
    } else {
        TB_INIT = false;
        debug_msg("Trackball initialization failed!");
    }

    // Initialize RTC
    pca_select(0);
    if (!rtc.begin()) {
        debug_msg("Can't find RTC!");
        RTC_INIT = false;
        while (1) sleep_ms(10);
    } else {
        RTC_INIT = true;
        debug_msg("Found RTC!");

        if (!rtc.initialized() || rtc.lostPower()) {
            debug_msg("RTC date/time NOT set!");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
            debug_msg("RTC date/time is now set!");
        }

        rtc.start();
        float drift = 43;
        float period_sec = (7 * 86400);
        float deviation_ppm = (drift / period_sec * 1000000);
        float drift_unit = 4.34;
        int offset = round(deviation_ppm / drift_unit);
        debug_msg("Offset is ");
        printf("%d\n", offset);
    }
}

void loop() {
    if (SD_INIT) {
        debug_msg("SD read/write OK!");
    } else {
        debug_msg("SD read/write NOT OK!");
    }

    if (TB_INIT) {
        pca_select(1);
        cycleTrackballColors();
        if (trackball.changed()) {
            int16_t x = (trackball.right() - trackball.left()) * 5;
            int16_t y = (trackball.down() - trackball.up()) * 5;
            trackball.setRGBW(x + y, x + y, x + y, 128);
            if (x != 0 || y != 0) {
                Mouse.move(x, y, 0);
                tft.setCursor(x, y);
                debug_msg("TB MOVED!");
            }
            if (trackball.click()) {
                Mouse.press(MOUSE_LEFT);
                debug_msg("TB CLICKED!");
                trackball.setRGBW(x + y, x + y, x + y, 128);
            } else if (trackball.release()) {
                if (Mouse.isPressed(MOUSE_LEFT)) {
                    Mouse.release(MOUSE_LEFT);
                    debug_msg("TB RELEASED!");
                    trackball.setRGBW(x + y, x + y, x + y, 128);
                }
            }
        }
    }
}

int main() {
    setup();
    while (true) {
        loop();
        sleep_ms(100);
    }
}
