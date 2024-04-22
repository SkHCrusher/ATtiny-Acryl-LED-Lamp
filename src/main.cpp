// Additional libraries
#include <Arduino.h>
#include <EEPROM.h>
#include <TinyButton.h>
#include <tinyNeoPixel_Static.h>

// Function declarations
byte getAnimationDelay(bool bootMode);
byte getColorId(bool bootMode);
uint32_t getLedColor(byte colorId);
uint32_t Wheel(byte WheelPos);
void btnOneClick();
void btnTwoClick();
void doAnimation();
void setModeDefaultValues(bool bootMode);

// LED settings
#define LED_PIN 0      // Pin to which the LED strip is connected
#define LED_COUNT 9    // Number of LEDs
byte brightness = 255; // Brightness of the LEDs from 0 to 255
int colorCount = 7;    // Number of individual colors for the static mode
byte colors[7][3] = {
    {255, 0, 0}, {255, 255, 0}, {0, 255, 0},    {0, 255, 255},
    {0, 0, 255}, {255, 0, 255}, {255, 255, 255}}; // Definition of colors for
                                                  // static mode
byte pixels[LED_COUNT *
            3]; // Variable is required for the tinyNeoPixel_Static library
tinyNeoPixel leds = tinyNeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800,
                                 pixels); // LED Stripe initialization

// Buttons Definition
#define BUTTON_PIN_1 1 // Pin of the first button / change mode
#define BUTTON_PIN_2                                                           \
  2 // Pin of the second button / change colors or animation speed
TinyButton btnOne(BUTTON_PIN_1);
TinyButton btnTwo(BUTTON_PIN_2);

// Internal variables
byte mode = 0;            // Current mode. 0 = Static colors, 1 = Rainbow
byte colorId = 0;         // Current color ID (static mode)
int animationStep = 0;    // Current step of the animation
int animationDelay = 250; // Current delay of the animation per step
unsigned long nextAnimationStep = 0; // Time of the next animation step
unsigned long currentTime = 0;       // Current time of the script

void setup() {
  // LED setup
  pinMode(LED_PIN, OUTPUT); // Needed for tinyNeoPixel_Static
  leds.begin();
  leds.setBrightness(brightness);

  // Register events for the buttons
  btnOne.attachClick(btnOneClick);
  btnTwo.attachClick(btnTwoClick);

  // Loading settings from the memory
  mode = EEPROM.read(0);
  setModeDefaultValues(true);
}

void loop() {
  // Remember current time
  currentTime = millis();

  // Trigger button logic
  btnOne.tick();
  btnTwo.tick();

  // Run animation
  doAnimation();
}

// Event, which is executed with a normal click of the first button
// = Changing the mode
void btnOneClick() {
  // Switch to the next mode
  mode = (mode < 1) ? (mode + 1) : 0;

  // Remember mode in memory
  EEPROM.write(0, mode);

  // Load default values for this mode
  setModeDefaultValues(false);
}

// Event, which is executed with a normal click of the second button
// = Change colors or animation speed
void btnTwoClick() {
  // What mode are we in
  // 0 = Static colors
  // 1 = Rainbow
  switch (mode) {
  case 0:
    // Switch one color further
    colorId = (colorId < (colorCount - 1)) ? (colorId + 1) : 0;

    // Remember color in memory
    EEPROM.write(1, colorId);
    break;
  case 1:
    // Adjust animation speed
    animationDelay = (animationDelay < 50) ? (animationDelay + 10) : 10;

    // Remember animation speed in memory
    EEPROM.write(2, animationDelay);
    break;
  }
}

// Set default values of the current mode
void setModeDefaultValues(bool bootMode) {
  // What mode are we in
  // 0 = Static colors
  // 1 = Rainbow
  switch (mode) {
  case 0:
    // Get and set color ID
    colorId = getColorId(bootMode);

    // Set animation speed to 250ms
    animationDelay = 250;

    // If the function was not called from the setup function, remember the
    // current color ID in the memory
    if (!bootMode)
      EEPROM.write(1, colorId);
    break;

  case 1:
    // Get and set current animation speed
    animationDelay = getAnimationDelay(bootMode);

    // If the function was not called from the setup function, remember the
    // current animation speed in the memory
    if (!bootMode)
      EEPROM.write(2, animationDelay);
    break;
  }
}

// Logic for the animation
void doAnimation() {
  // Check whether the next animation step may be executed
  if (nextAnimationStep <= currentTime) {
    // What mode are we in
    // 0 = Static colors
    // 1 = Rainbow
    switch (mode) {
    case 1:
      // Variable for the color position in the rainbow
      static uint16_t j = 0;

      // Set pixels in the respective colors of the current position of the
      // rainbow
      for (uint16_t i = 0; i < LED_COUNT; i++) {
        leds.setPixelColor(i, Wheel(((i * 256 / LED_COUNT) + j) & 255));
      }

      // Update LEDs
      leds.show();

      // Increase color position in the rainbow
      j = (j + 1) % 256;
      break;

    case 0:
    default:
      // Set all LEDs to the same color
      leds.fill(getLedColor(colorId), 0, LED_COUNT);

      // Update LEDs
      leds.show();
      break;
    }

    // Set time for the next animation step
    nextAnimationStep = currentTime + animationDelay;
  }
}

// Help function to get the static LED color, so that the call in the code is
// clearer
uint32_t getLedColor(byte colorId) {
  // Get RGB values from the color array defined in the header
  return leds.Color(colors[colorId][0], colors[colorId][1], colors[colorId][2]);
}

// Helper function to get the color ID
byte getColorId(bool bootMode) {
  // Get current color ID
  byte tmpColorId = colorId;

  // When the function is called up in the setup
  if (bootMode) {
    // Get color ID from the memory
    tmpColorId = EEPROM.read(1);
  }

  // Return color ID. If the ID does not correspond to a valid value, send the
  // color ID 0
  return (tmpColorId < 0 || tmpColorId >= colorCount) ? 0 : tmpColorId;
}

// Helper function for getting the animation speed
byte getAnimationDelay(bool bootMode) {
  // Get current animation speed
  byte tmpAnimationDelay = animationDelay;

  // When the function is called up in the setup
  if (bootMode) {
    // Get animation speed from memory
    tmpAnimationDelay = EEPROM.read(2);
  }

  // Return animation speed. If the speed does not have a valid value, return
  // the speed 10ms
  return (tmpAnimationDelay < 10 || tmpAnimationDelay > 50) ? 10
                                                            : tmpAnimationDelay;
}

// Magic function for determining the color for the rainbow animation ;-)
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return leds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}