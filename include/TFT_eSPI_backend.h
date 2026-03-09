// include/backends/TFT_eSPI_backend.h
#pragma once
#ifdef GFX_BACKEND_TFT_eSPI

#include <TFT_eSPI.h>
#include "../DisplayBackend.h"
#include "../TouchBackend.h"

class TFT_eSPI_Display : public DisplayBackend {
private:
    TFT_eSPI tft;

public:
    void begin() override {
        tft.begin();
        tft.setRotation(1);           // adjust 0..3 as needed
        tft.fillScreen(TFT_BLACK);
    }

    void setRotation(uint8_t r) override { tft.setRotation(r); }
    void fillScreen(uint16_t c) override { tft.fillScreen(c); }
    void drawPixel(int16_t x, int16_t y, uint16_t c) override { tft.drawPixel(x, y, c); }
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t c) override { tft.drawLine(x0,y0,x1,y1,c); }
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) override { tft.drawRect(x,y,w,h,c); }
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) override { tft.fillRect(x,y,w,h,c); }
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t c) override { tft.drawCircle(x0,y0,r,c); }
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t c) override { tft.fillCircle(x0,y0,r,c); }

    void setTextColor(uint16_t c) override { tft.setTextColor(c); }
    void setTextSize(uint8_t s) override { tft.setTextSize(s); }
    void setCursor(int16_t x, int16_t y) override { tft.setCursor(x, y); }
    size_t print(const char *str) override { return tft.print(str); }

    int16_t width() const override { return tft.width(); }
    int16_t height() const override { return tft.height(); }
};

extern TFT_eSPI_Display tft_display;
inline DisplayBackend* display = &tft_display;

// -----------------------------------------------------------------------------
// Very simple touch wrapper (XPT2046)
// -----------------------------------------------------------------------------
#include <XPT2046_Touchscreen.h>

class XPT2046_Touch : public TouchBackend {
private:
    XPT2046_Touchscreen ts;

public:
    XPT2046_Touch() : ts(TOUCH_CS) {}   // TOUCH_CS defined in User_Setup.h

    void begin() override {
        ts.begin();
        ts.setRotation(1);   // match display rotation
    }

    bool touched() override {
        return ts.touched();
    }

    void read(int16_t &x, int16_t &y) override {
        TS_Point p = ts.getPoint();
        // Very rough mapping – you should calibrate properly
        x = map(p.x, 200, 3700, 0, tft_display.width());
        y = map(p.y, 240, 3800, 0, tft_display.height());
    }
};

extern XPT2046_Touch touchscreen;
inline TouchBackend* touch = &touchscreen;

#endif

4. main.cpp – Demo Sketchcpp

// src/main.cpp
#include <Arduino.h>

#define GFX_BACKEND_TFT_eSPI    // must match platformio.ini
#include "DisplayBackend.h"
#include "TouchBackend.h"

uint32_t lastTouchTime = 0;
int16_t touchX = -1, touchY = -1;
uint8_t demoMode = 0;
uint32_t lastChange = 0;

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\nWaveshare 4\" ILI9486 TFT Demo (TFT_eSPI backend)");

    display->begin();
    touch->begin();

    display->fillScreen(TFT_BLACK);
    display->setTextColor(TFT_WHITE);
    display->setTextSize(2);
    display->setCursor(20, 20);
    display->print("Waveshare 4\" Touch Demo");
    delay(1500);
}

void loop() {
    uint32_t now = millis();

    // Simple mode cycling every 8 seconds
    if (now - lastChange > 8000) {
        demoMode = (demoMode + 1) % 4;
        lastChange = now;
        display->fillScreen(TFT_BLACK);
    }

    // Touch detection
    if (touch->touched()) {
        touch->read(touchX, touchY);
        lastTouchTime = now;

        // Draw touch point
        display->fillCircle(touchX, touchY, 8, TFT_RED);
        display->setCursor(touchX + 12, touchY - 10);
        display->setTextColor(TFT_WHITE, TFT_RED);
        display->setTextSize(1);
        display->print("TOUCH");
    }

    // Different demo scenes
    switch (demoMode) {
        case 0: // Rainbow fade + text
            static uint8_t hue = 0;
            uint16_t color = display->color565(hue * 2, 255 - hue * 2, 128 + hue);
            display->fillScreen(color);
            display->setTextColor(TFT_WHITE);
            display->setTextSize(3);
            display->setCursor(40, 100);
            display->print("Hello");
            display->setCursor(60, 160);
            display->print("World!");
            hue = (hue + 1) % 128;
            break;

        case 1: // Shapes animation
            display->drawRect(50, 50, display->width()-100, display->height()-100, TFT_YELLOW);
            display->drawCircle(display->width()/2, display->height()/2, 80, TFT_CYAN);
            display->fillTriangle(100, 200, 200, 100, 300, 200, TFT_MAGENTA);
            display->drawLine(0, 0, display->width(), display->height(), TFT_GREEN);
            break;

        case 2: // Grid + random pixels
            for (int i = 0; i < 200; i++) {
                int x = random(display->width());
                int y = random(display->height());
                display->drawPixel(x, y, random(0xFFFF));
            }
            display->setTextColor(TFT_YELLOW);
            display->setTextSize(2);
            display->setCursor(30, display->height() - 60);
            display->print("Random pixels");
            break;

        case 3: // Touch coordinate display
            display->setTextColor(TFT_LIGHTGREY, TFT_BLACK);
            display->setTextSize(2);
            display->setCursor(20, 80);
            display->print("Touch to test");
            if (touchX >= 0 && touchY >= 0) {
                display->setCursor(20, 120);
                display->printf("X: %d   ", touchX);
                display->setCursor(20, 150);
                display->printf("Y: %d   ", touchY);
            }
            break;
    }

    delay(60);  // ~16 fps
}


