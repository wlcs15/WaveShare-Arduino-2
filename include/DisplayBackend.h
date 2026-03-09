#pragma once
#include <Arduino.h>

class DisplayBackend {
public:
    virtual ~DisplayBackend() = default;

    virtual void begin() = 0;
    virtual void setRotation(uint8_t rotation) = 0;
    virtual void fillScreen(uint16_t color) = 0;

    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) = 0;
    virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) = 0;
    virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) = 0;

    virtual void setTextColor(uint16_t c) = 0;
    virtual void setTextColor(uint16_t fg, uint16_t bg) = 0;
    virtual void setTextSize(uint8_t s) = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;

    virtual size_t print(const char *str) = 0;
    virtual size_t print(const __FlashStringHelper *str) = 0;

    virtual uint16_t color565(uint8_t r, uint8_t g, uint8_t b) = 0;

    // Removed 'const' here
    virtual int16_t width() = 0;
    virtual int16_t height() = 0;
};

extern DisplayBackend* display;
