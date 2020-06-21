#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

void setup() { 
  LEDS.addLeds<WS2813, LED_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(15);
}

void loop() {
  
/*    Para calibrar observar el orden de los colores
      en nuestro caso "GRB"
      y editar el setup addLeds como:
      LEDS.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
*/

    leds[0] = CRGB::Red; leds[0].fadeLightBy( 50 );
    FastLED.show();
    leds[1] = CRGB::Green; leds[1].fadeLightBy( 50 );
    FastLED.show();
    leds[2] = CRGB::Blue; leds[2].fadeLightBy( 50 );
    FastLED.show();
  
}
