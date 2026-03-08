#include "DisplayBackend.h"
#include "TouchBackend.h"
// ... other includes

void setup() {
    Serial.begin(115200);

    #if defined(GFX_BACKEND_WAVESHARE_ILI9486)
        // init code specific if needed
    #endif

    display->begin();
    display->setRotation(1);
    display->fillScreen(0x0000);

    // your app init
}

void loop() {
    // your logic – use only display->xxx() and touch->xxx()
}

