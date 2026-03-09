// include/TouchBackend.h
#ifdef HACK
#pragma once
#include <Arduino.h>

class TouchBackend {
public:
    virtual ~TouchBackend() = default;
    virtual void begin() = 0;
    virtual bool isPressed() = 0;
    virtual void readPoint(int16_t &x, int16_t &y) = 0;
    // Add calibration methods later if needed
};

extern TouchBackend* touch;  // Global pointer, set in setup()
#else 
// include/TouchBackend.h
#pragma once
#include <Arduino.h>

class TouchBackend {
public:
    virtual ~TouchBackend() = default;
    virtual void begin() = 0;
    virtual bool touched() = 0;
    virtual void read(int16_t &x, int16_t &y) = 0;   // raw or mapped coordinates
};

extern TouchBackend* touch;
#endif
