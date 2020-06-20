 /*
 * Led strip WS2815 control for IR
 *
 * State testing, developer c2mismo 2020.
 * License GNU, see at the end.
 */



#include <FastLED.h>
#include <IRremote.h>
//Conf FstaLed
#define LED_PIN     5
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

int option;
byte led = 0;

//byte valHue = 0, valSat = 0, valVal = 0;
byte valHue = 0, valSat = 255, valVal = 150;
bool  flagHue = 0;

//Conf IRremote
const byte RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results IR;
byte btnIR;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  LEDS.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); } FastLED.show();
}

void loop() {
  if (irrecv.decode(&IR)) {
    if ( IR.value == 0x1FE48B7 ){ btnIR = 1; }
    if ( IR.value == 0x1FE7887 ){ btnIR = 2; }
    if ( IR.value == 0x1FE807F ){ btnIR = 3; }
    if ( IR.value == 0x1FE40BF ){ btnIR = 4; }
    if ( IR.value == 0x1FEC03F ){ btnIR = 5; }
    if ( IR.value == 0x1FEE01F ){ btnIR = 6; }
    if ( IR.value == 0x1FE10EF ){ btnIR = 7; }
    if ( IR.value == 0x1FE906F ){ btnIR = 8; }
    if ( IR.value == 0x1FE50AF ){ btnIR = 9; }
    if ( IR.value == 0x1FEF807 ){ btnIR = 10; }
    if ( IR.value == 0x1FE30CF ){ btnIR = 11; }
    if ( IR.value == 0x1FEB04F ){ btnIR = 12; }
    if ( IR.value == 0x1FE708F ){ btnIR = 13; }
    ledWrite(btnIR);
    irrecv.resume();
    FastLED.show();
    delay(10);
  }
}





void ledWrite(byte B){

    Serial.print("Boton = ");
    Serial.println(B);
// Rojo
  if (B == 3){
    if (valHue > 128 && valHue < 213) { valHue = 213; flagHue = 1;}
    else if (valHue < 128 && valHue > 43) { valHue = 43; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue >= 255){ valHue = 0; }
      else if (valHue > 42 && valHue < 128){ flagHue = 0; valHue = 43; }
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 0){ valHue = 255; }
      else if (valHue <= 213 && valHue > 44){ flagHue = 1; valHue = 213; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
// Amarillo
  if(B == 6) {
    if (valHue >= 170 && valHue < 255) { valHue = 255; flagHue = 1;}
    else if (valHue < 170 && valHue > 85) { valHue = 85; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue <= 255 && valHue > 170){ valHue = 0; }
      else if (valHue >= 85 && valHue < 170){ flagHue = 0; valHue = 85; }
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 0){ flagHue = 1; valHue = 0; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
//Verde
  if (B == 4){
    if (valHue >= 213 && valHue < 255) { valHue = 43; flagHue = 1;}
    else if (valHue >= 0 && valHue < 43) { valHue = 43; flagHue = 1;}
    else if (valHue < 213 && valHue > 128) { valHue = 128; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue == 255){ valHue = 0; }
      else if (valHue >= 128){ flagHue = 0; valHue = 128; }
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 43){ flagHue = 1; valHue = 43; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
//Agua Marina
  if(B == 7) {
    if (valHue <= 85) { valHue = 85; flagHue = 1;}
    else if (valHue > 170) { valHue = 170; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue >= 170){ flagHue = 0; valHue = 170; }
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 85){ flagHue = 1; valHue = 85; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
//Azul
  if (B == 5){
    if (valHue >= 85 && valHue < 170) { valHue = 170; flagHue = 1;}
    else if (valHue > 213 || valHue < 43) { valHue = 213; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue >= 255){ flagHue = 0; valHue = 255; }//  254
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 128){ flagHue = 1; valHue = 128; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
//Purpura
  if (B == 8){
    if (valHue >= 85 && valHue < 170) { valHue = 170; flagHue = 1;}  // Valor extremo 1:=
    else if (valHue < 85) { valHue = 255; flagHue = 0;}

    else if (flagHue == 1) {
      if (valHue >= 213){ flagHue = 0; valHue = 212; }
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {
      if (valHue <= 170){ flagHue = 1; valHue = 171; }
      else { valHue = valHue - 1; }
    }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }





// Sat Saturacion
  if(B == 9) {
    if (valSat <= 9) { valSat = 0; }
    if (valSat > 9) { valSat = valSat - 10; }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
  if(B == 10) {
    if (valSat < 245) { valSat = valSat + 10; }
    if (valSat >= 245) { valSat = 255; }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
// Value Brillo (ON OFF)
  if(B == 1) {
    if (valVal <= 9) { valVal = 0; }
    if (valVal > 9) { valVal = valVal - 10; }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }
  if(B == 2) {
    if (valVal < 245) { valVal = valVal + 10; }
    if (valVal >= 245) { valVal = 255; }
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
  }


  Serial.print("Boton = ");
  Serial.print(B);

  Serial.print("   Hue = "), Serial.print(valHue);
  Serial.print("   Sat = "), Serial.print(valSat);
  Serial.print("   Val = "), Serial.println(valVal);
}
