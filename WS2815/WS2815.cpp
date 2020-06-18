#include "arduino.h"
#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  
    leds[0] = CRGB::White; FastLED.show();
    leds[1] = CRGB::GhostWhite; FastLED.show();
    //leds[2] = CRGB::Red; FastLED.show();

  
}