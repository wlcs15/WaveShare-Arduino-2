// src/TFT_eSPI_Display.cpp

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "config_pins.h"
#include "DisplayBackend.h"
#include "TouchBackend.h"

// If TOUCH_CS is not defined in User_Setup.h (or not included early enough), define a default here
// CHANGE THIS TO YOUR ACTUAL TOUCH CS PIN (usually 4, 9 or 10 on Waveshare shields)
#ifndef TOUCH_CS
  #define TOUCH_CS 4
#endif

// ────────────────────────────────────────────────
// TFT_eSPI Display Backend Implementation
// ────────────────────────────────────────────────

class TFT_eSPI_Display final : public DisplayBackend {
private:
    TFT_eSPI tft;

public:
    void begin() override {
        tft.begin();
        tft.setRotation(1);           // 0–3 — adjust if needed
        tft.fillScreen(tft.color565(0,0,0));  // black
    }

    void setRotation(uint8_t r) override {
        tft.setRotation(r);
    }

    void fillScreen(uint16_t color) override {
        tft.fillScreen(color);
    }

    void drawPixel(int16_t x, int16_t y, uint16_t color) override {
        tft.drawPixel(x, y, color);
    }

    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) override {
        tft.drawLine(x0, y0, x1, y1, color);
    }

    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
        tft.drawRect(x, y, w, h, color);
    }

    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
        tft.fillRect(x, y, w, h, color);
    }

    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) override {
        tft.drawCircle(x0, y0, r, color);
    }

    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) override {
        tft.fillCircle(x0, y0, r, color);
    }

    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) override {
        tft.drawRoundRect(x, y, w, h, r, color);
    }

    void setTextColor(uint16_t c) override {
        tft.setTextColor(c);
    }

    void setTextColor(uint16_t fg, uint16_t bg) override {
        tft.setTextColor(fg, bg);
    }

    void setTextSize(uint8_t s) override {
        tft.setTextSize(s);
    }

    void setCursor(int16_t x, int16_t y) override {
        tft.setCursor(x, y);
    }

    size_t print(const char *str) override {
        return tft.print(str);
    }

    size_t print(const __FlashStringHelper *str) override {
        return tft.print(str);
    }

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b) override {
        return tft.color565(r, g, b);
    }

    // Removed 'const' to match TFT_eSPI signature
    int16_t width() override {
        return tft.width();
    }

    int16_t height() override {
        return tft.height();
    }
};

// Global instance + pointer (linker needs this definition)
static TFT_eSPI_Display tft_display_instance;
DisplayBackend* display = &tft_display_instance;


// ────────────────────────────────────────────────
// XPT2046 Touch Backend Implementation
// ────────────────────────────────────────────────

class XPT2046_Touch final : public TouchBackend {
private:
    XPT2046_Touchscreen ts;

public:
    XPT2046_Touch() : ts(TOUCH_CS) {}   // TOUCH_CS now guaranteed to exist

    void begin() override {
        ts.begin();
        ts.setRotation(1);   // Match display rotation
    }

    bool touched() override {
        return ts.touched();
    }

    void read(int16_t &x, int16_t &y) override {
        TS_Point p = ts.getPoint();
        // Rough calibration – replace with proper values later
        x = map(p.x, 200, 3700, 0, tft_display_instance.width());
        y = map(p.y, 240, 3800, 0, tft_display_instance.height());
        x = constrain(x, 0, tft_display_instance.width() - 1);
        y = constrain(y, 0, tft_display_instance.height() - 1);
    }
};

// Global instance + pointer
static XPT2046_Touch touchscreen_instance;
TouchBackend* touch = &touchscreen_instance;
