// src/main.cpp – minimal direct TFT_eSPI test

#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n=== MINIMAL TFT_eSPI TEST START ===");

    Serial.println("Calling tft.begin()...");
    tft.begin();
    Serial.println("tft.begin() returned");

    Serial.print("Rotation test - trying 0,1,2,3...");
    for (uint8_t rot = 0; rot < 4; rot++) {
        tft.setRotation(rot);
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(3);
        tft.setCursor(40, 80);
        tft.print("ROT ");
        tft.print(rot);
        tft.setCursor(40, 140);
        tft.print("TEST");
        Serial.print(" Rotation ");
        Serial.print(rot);
        Serial.println(" set");
        delay(3000);  // 3 seconds per rotation
    }

    Serial.println("=== TEST CYCLE DONE ===");
}

void loop() {
    Serial.println("loop alive...");
    delay(2000);
}

