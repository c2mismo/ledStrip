#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

int option;
byte led = 0;

byte valHue = 0, valSat = 0, valVal = 15;


void setup() { 
  Serial.begin(9600);
  LEDS.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness(15);
  for (byte led = 0; led < NUM_LEDS; led = led + 1) { leds[led] = CRGB::White; } FastLED.show();
}

void loop() {

  if (Serial.available()>0){
    option=Serial.read();
    if(option=='1') {
      if (valHue > 4) { valHue = valHue - 5; }
      if (valHue <= 4) { valHue = 0; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Hue = ");
      Serial.println(valHue);
    }
    if(option=='7') {
      if (valHue < 245) { valHue = valHue + 5; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Hue = ");
      Serial.println(valHue);
    }
    if(option=='2') {
      if (valSat > 4) { valSat = valSat - 5; }
      if (valSat <= 4) { valSat = 0; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Sat = ");
      Serial.println(valSat);
    }
    if(option=='8') {
      if (valSat < 245) { valSat = valSat + 5; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Sat = ");
      Serial.println(valSat);
    }
    if(option=='3') {
      if (valVal > 4) { valVal = valVal - 5; }
      if (valVal <= 4) { valVal = 0; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Val = ");
      Serial.println(valVal);
    }
    if(option=='9') {
      if (valVal < 245) { valVal = valVal + 5; }
      leds[0] = CHSV( valHue, valSat, valVal);
      leds[1] = CHSV( valHue, valSat, valVal);
      leds[2] = CHSV( valHue, valSat, valVal);
      Serial.print("Val = ");
      Serial.println(valVal);
    }
  }

//  int color = leds[0]; Serial.println(color); Devuelve Encendido "1" o apagado "0"

  FastLED.show();
    
    
}
