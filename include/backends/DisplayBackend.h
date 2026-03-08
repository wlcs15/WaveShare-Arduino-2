// include/DisplayBackend.h
#pragma once
#include <Arduino.h>

class DisplayBackend {
public:
    virtual ~DisplayBackend() = default;
    virtual void begin() = 0;
    virtual void fillScreen(uint16_t color) = 0;
    virtual void setRotation(uint8_t r) = 0;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size = 2) = 0;
    // ... more methods you actually need (rect, line, bitmap etc.)
    virtual int16_t width() const = 0;
    virtual int16_t height() const = 0;
};

extern DisplayBackend* display;   // global pointer – set in setup()

