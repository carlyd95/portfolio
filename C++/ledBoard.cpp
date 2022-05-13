/*
  Filename: ledBoard.cpp
  Author: Carlton Dunlap
  Date: 09/23/2021
  Description: creates instance of NeoPixel strip and conatians
    methods and variable to execute effects on it.
*/

#include "ledBoard.h"

// Static, constant, non-integral variables must be initilized in the source file (leave out static)
const float ledBoard::_kInchesInMeter = 39.37007874;

// Member initilization constructor
ledBoard::ledBoard(const uint8_t kPixelCount,
      const uint8_t kPixelPin,
      const uint8_t kHallEffectPin,
      const uint8_t kStripLengthMeter,
      const uint8_t kPixelsPerStrip,
      const float kWheelCircum,
      const uint8_t kMagnetCount) : 
  _kPixelCount(kPixelCount),
  _pos2(kPixelCount),
  _kMaxPixel(kPixelCount - 1),
  _kPixelPin(kPixelPin),
  _kHallEffectPin(kHallEffectPin),
  // Calculates how many pixels to move per change event 
  _kPixelsPerChange((kWheelCircum  / (kMagnetCount * 2)) / ((kStripLengthMeter * _kInchesInMeter) / kPixelsPerStrip)),
  strip(kPixelCount, kPixelPin),
  _appliedEffect(1),
  _swipeLength(_kDefaultSwipeLength) {
    // Initialize strip object
    strip.Begin();
    // Sets HE pin as input
    pinMode(_kHallEffectPin, INPUT);
  }

/* 
    UTILITIES
*/

// Clears strip
void ledBoard::clearStrip() {
  for (uint8_t i = 0; i < _kPixelCount; i++) {
    strip.SetPixelColor(i, RgbColor(0,0,0));
  }
}

// Resets variables used during effects (for changing effect)
void ledBoard::resetPos () {
  _rainbowPos = 0;
  _pos = 0;
  _pos2 = _kPixelCount;

}

// Sets which effect should be used
void ledBoard::setEffect (uint8_t effect) {
  _appliedEffect = effect;
}

// Sets swipe length to be used if effect requires one
void ledBoard::setSwipeLength (uint8_t swipeLength) {
  _swipeLength = swipeLength;
}

// Input a value 0 to 255 to get a color value (cycles r-g-b-r)
// Saves rgb values as private member vars
void ledBoard::colorWheel(uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85) {
    _r = 255 - pos * 3;
    _g = 0;
    _b = pos * 3;
  } else if (pos < 170) {
    pos -= 85;
    _r = 0;
    _g = pos * 3;
    _b = 255 - pos * 3;
  } else {
    pos -= 170;
    _r = pos * 3;
    _g = 255 - pos * 3;
    _b = 0;
  }
}

/*
    EFFECTS
*/

// Effect #1 -- continually casts part of a rainbow which moves with the board
void ledBoard::rainbowRoll() {
  for (uint8_t i = 0; i < _kPixelCount; i++) {
    // Ensures _rainbowPos is within range
    if (_rainbowPos < 0) {
      _rainbowPos += 255;
    } else if (_rainbowPos > 255) {
      _rainbowPos -= 255;
    }
    // Updates rgb from _rainbowPos and fills strip
    colorWheel(_rainbowPos);
    strip.SetPixelColor(i, RgbColor(_r, _g, _b));
    // Increases _rainbowPos
    _rainbowPos++;
  }
  // Resets _rainbowPos from fading down the whole strip
  _rainbowPos -= _kMaxPixel + _kPixelsPerChange;
  strip.Show();
}


// Effect #2 -- swipe effect with changing color
void ledBoard::fadeRainbowSwipe() {
  // Checks if front pixel is off the board and corrects if so
  if (_pos >= _kPixelCount) {
    _pos -= _kMaxPixel + _swipeLength;
  }

  // Clears pixels before lighting new ones
  clearStrip();

  // Lights up all valid pixels in swipe range
  for (int8_t i = _pos; i < _pos + _swipeLength; i++) {
    if (_rainbowPos > 255) {
      _rainbowPos = 0;
    }
    if (i >= 0) {
      // Updates rgb from _rainbowPos and fills strip
      colorWheel(_rainbowPos);
      strip.SetPixelColor(i, RgbColor(_r, _g, _b));
    }
  }
  strip.Show();
  _rainbowPos++;
  // Updates the pixels position 
  _pos = round(_pos + _kPixelsPerChange);
}


// Effect #3 -- swipe effect with changing color
void ledBoard::solidRainbowSwipe() {
  // Checks if front pixel is off the board and corrects if so
  if (_pos >= _kPixelCount) {
    _pos -= _kMaxPixel + _swipeLength;
    _rainbowPos++;
  }

  // Clears pixels before lighting new ones
  clearStrip();

  // Lights up all valid pixels in swipe range
  for (int8_t i = _pos; i < _pos + _swipeLength; i++) {
    if (_rainbowPos > 255) {
      _rainbowPos = 0;
    }
    if (i >= 0) {
      // Updates rgb from _rainbowPos and fills strip
      colorWheel(_rainbowPos);
      strip.SetPixelColor(i, RgbColor(_r, _g, _b));
    }
  }
  strip.Show();
  // Updates the pixels position 
  _pos = round(_pos + _kPixelsPerChange);
}


// Effect #4 -- swipe effect with changing rainbow gradient
void ledBoard::gradientRainbowSwipe() {
  // Checks if front pixel is off the board and corrects if so
  if (_pos >= _kPixelCount) {
    _pos -= _kMaxPixel + _swipeLength;
  }

  // Clears pixels before lighting new ones
  clearStrip();
  _pos2 = 0;
  // Lights up all valid pixels in swipe range
  for (int8_t i = _pos + _swipeLength - 1; i >= _pos; i--) {
    if (_rainbowPos > 255) {
      _rainbowPos = 0;
    }
    if (i >= 0) {
      // Updates rgb from _rainbowPos and fills strip
      colorWheel(_rainbowPos);
      strip.SetPixelColor(i, RgbColor(_r, _g, _b));
      _rainbowPos++;
      _pos2++;
    }
  }
  strip.Show();
  // Updates the pixels position 
  _rainbowPos -= _pos2 + 1;
  _pos = round(_pos + _kPixelsPerChange);
}

/*
    EFFECT APPLIERS
*/

// Runs one iteration of an effect via switch based on _appliedEffect
void ledBoard::applyEffect() {
  switch(_appliedEffect) {
      case 1:
        rainbowRoll();
        break;
      case 2:
        fadeRainbowSwipe();
        break;
      case 3:
        solidRainbowSwipe();
        break;
      case 4:
        gradientRainbowSwipe();
        break;
      default:
        rainbowRoll();
    }
}

// Checks if hall effect sensor has experienced a changed and runs on iteration of the effect if so
void ledBoard::hallEffect () {
  // Checks status of hall effect
  _curr = digitalRead(_kHallEffectPin);
  // Checks if HE status has changed from last iteration
  if (_curr != _prev) {
    // Updates previous HE status
    _prev = _curr;
    applyEffect();
  }
}

/*
// Effect #6 -- single swipe color effect
void colorSwipe() {

    # Pulls global variables
    global _pos
    global _kMaxPixel
    global PIXELS
    global _kPixelsPerChange;
    color = R
    global DEFAULT_SWIPE_LENGTH
    _swipeLength = DEFAULT_SWIPE_LENGTH
    if len(argv) > 2:
      _swipeLength = int(argv[2])

    if _swipeLength > 15:
      _swipeLength = 15

    # Checks if front pixel is off the board and corrects if so
    if _pos + _swipeLength > _kMaxPixel:
        _pos -= _kMaxPixel

    # Clears pixels before lighting new ones
    PIXELS.fill((0,0,0))

    # Lights up all valid pixels in swipe range
    for i in range(int(_pos), _swipeLength + int(_pos)):
        if i < _kMaxPixel:
            PIXELS[i] = color
    PIXELS.show()

    # Updates the pixels position
    _pos += _kPixelsPerChange;
}

// Effect #7 -- alternating color swipe effect
void  multiSwipe() {
    # Pulls global variables
    global _pos
    global _kMaxPixel
    global DEFAULT_SWIPE_LENGTH
    _swipeLength = DEFAULT_SWIPE_LENGTH
    if len(argv) > 2:
      _swipeLength = int(argv[2])
    global PIXELS
    global _kPixelsPerChange;
    global MSCOLOR

    if _swipeLength > 40:
      _swipeLength = 40

    colors = (C, Y, M)

    # Gets number of arguments supplied
    nColors = len(colors)

    # Corrects position after each swipe
    # Changes color after each swipe
    if _pos + _swipeLength > NUM_OF_PIXELS:
        _pos -= _kMaxPixel
        MSCOLOR = MSCOLOR + 1 if MSCOLOR < nColors - 1 else 0

    # Clears pixels before lighting new ones
    PIXELS.fill((0, 0, 0))

    # Lights up all valid pixels in swipe range
    for i in range(int(_pos), _swipeLength + int(_pos)):
        if i <= _kMaxPixel:
            if i < 0:
                PIXELS[i] = colors[MSCOLOR - 1]
            else:
                PIXELS[i] = colors[MSCOLOR]
    PIXELS.show()
    # Updates the pixels position
    _pos += _kPixelsPerChange;
}

// Effect #3 - one color per board length
def rainbowFade():

    # Pulls global variables
    global _kMaxPixel
    global PIXELS
    global _rainbowPos
    

    PIXELS.fill((0, 0, 0))

    for pixel in range(_kMaxPixel):
      if _rainbowPos > 255:
        _rainbowPos = 0
      PIXELS[pixel] = wheel(_rainbowPos)
    _rainbowPos += 1
    PIXELS.show()

// Effect #4 -- intersecting swipes that displays their addittive color
void additiveLight() {
  global C, Y, M, R, G, B
  global _pos, _pos2, _kPixelsPerChange;, _kMaxPixel
  global XCOLORPAIR

  global DEFAULT_SWIPE_LENGTH
  _swipeLength = DEFAULT_SWIPE_LENGTH
  if len(argv) > 2:
    _swipeLength = int(argv[2])


  colorpair = [[R, G, Y], [G, B, C], [B, R, M]]

  if _swipeLength > 20:
      _swipeLength = 20

  # Checks if front pixel is off the board and corrects if so
  if _pos > _kMaxPixel:
      _pos = 0 - _swipeLength
      XCOLORPAIR = XCOLORPAIR + 1 if XCOLORPAIR < 2 else 0
  # Checks if front pixel is off the board and corrects if so
  if _pos2 < 0:
      _pos2 = NUM_OF_PIXELS + _swipeLength

  # Clears pixels before lighting new ones
  PIXELS.fill((0,0,0))

  # Lights up all valid pixels in swipe range
  
  for i in range(int(_pos), _swipeLength + int(_pos)):
    if i < NUM_OF_PIXELS and i > -1:
      PIXELS[i] = colorpair[XCOLORPAIR][0]
  for i in range(int(_pos2) - _swipeLength, int(_pos2)):
    if i < NUM_OF_PIXELS and i > -1:
      PIXELS[i] = colorpair[XCOLORPAIR][1]
  for i in range(int(_pos), _swipeLength + int(_pos)):
    if i in range(int(_pos2) - _swipeLength, int(_pos2)):
      PIXELS[i] = colorpair[XCOLORPAIR][2]

  # Applies pixel changes
  PIXELS.show()

  # Updates the pixels position
  _pos += _kPixelsPerChange;
  _pos2 -= _kPixelsPerChange;
}
*/

