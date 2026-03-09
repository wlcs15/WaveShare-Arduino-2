//#include "config_pins.h"
//
// These values were taken from the semi-working Waveshare LCD_Touch example
// 
#define ILI9486_DRIVER
#define TFT_WIDTH  480
#define TFT_HEIGHT 320

#define TFT_CS   10   // Chip select
#define TFT_DC   9    // Data/Command
#define TFT_RST  -1   // Reset (or real pin if used)
#define TOUCH_CS 4    // XPT2046 touch chip select – adjust to your shield!

#define SPI_FREQUENCY  40000000
