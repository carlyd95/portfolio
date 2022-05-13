#include "ledBoard.h"

// NeoPixel constants
const uint8_t   kPixelCount = 20;
const uint8_t   kPixelPin = 14; // Ignored for Esp8266 but need to declare
// Hall Effect pin constant
const uint8_t   kHallEffectPin = 1;
// Configurable measured constants
const uint8_t   kStripLengthMeter = 1;
const uint8_t   kPixelsPerStrip = 60;
const float     kWheelCircum  = 8.5;
const uint8_t   kMagnetCount = 4;

// Instantiate ledBoard (strip obj, and effect methods and vars)
ledBoard ledBoard(kPixelCount, kPixelPin, kHallEffectPin, kStripLengthMeter, kPixelsPerStrip, kWheelCircum, kMagnetCount);


void setup() {
  for (int i = 0; i < 25; i++) {
    ledBoard.rainbowRoll3();
    delay(500);
  }
}


void loop() {
}
