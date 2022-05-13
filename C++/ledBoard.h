/*
  Filename: ledBoard.h
  Author: Carlton Dunlap
  Date: 09/23/2021
  Description: creates instance of NeoPixel strip and conatians
    methods and variable to execute effects on it.
*/

#ifndef ledBoard_h
#define ledBoard_h

#include "NeoPixelBus.h"

class ledBoard {
  private:
    // Static constants
    static const uint8_t  _kDefaultSwipeLength = 12;
    static const float    _kInchesInMeter; // static, constant, non-integral variables must be initilized in the source file
    // Measurement constants
    const uint8_t   _kPixelCount;
    const uint8_t   _kMaxPixel;
    const uint8_t   _kPixelPin;
    const uint8_t   _kHallEffectPin;
    const float     _kPixelsPerChange;
    // HE vars
    bool _curr, _prev;
    // Effect vars
    uint8_t _appliedEffect;
    uint8_t _swipeLength;
    uint8_t _r, _g, _b;
    float  _rainbowPos = 0;
    uint8_t _prevRainbowPos;
    int8_t _pos = 0;
    float   _pos2;
  public:
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip; 
    ledBoard(const uint8_t kPixelCount,
      const uint8_t kPixelPin,
      const uint8_t kHEPin,
      const uint8_t kStripLengthMeter,
      const uint8_t kPixelsPerStrip,
      const float kWheelCircum,
      const uint8_t kMagnetCount);
    // Utilities
    void clearStrip();
    void resetPos();
    void setEffect(uint8_t effect);
    void setSwipeLength(uint8_t swipeLength);
    void colorWheel(uint8_t pos);
    // Effects
    void rainbowRoll();
    void fadeRainbowSwipe();
    void solidRainbowSwipe();
    void gradientRainbowSwipe();
    // Apply effects
    void applyEffect();
    void hallEffect();
    // void testEffect(); -- loop
};

#endif
