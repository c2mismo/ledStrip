 /*
 * Led strip WS2815 control for IR
 *
 * State testing, developer c2mismo 2020.
 * License GNU, see at the end.
 */



#include <FastLED.h>
#include <IRremote.h>

                        //Config FastLed
const byte LED_PIN = 5;
const byte NUM_LEDS = 3;
int firstLed = 2;
int lastLed = 3;

CRGB leds[NUM_LEDS];

int option;
byte led = 0;

byte valHue = 128, valSat = 0, valVal = 0;
//byte valHue = 0, valSat = 255, valVal = 25;
byte lastValHue = valHue, lastValSat = valSat, lastValVal = valVal;
bool flagHue = 0;

                        //Config IRremote
const byte RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results IR;
byte btnIR;
byte lastB;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  LEDS.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
  if (firstLed > lastLed){int v = firstLed; firstLed = lastLed, lastLed = v;}
  firstLed = firstLed - 1;
  for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); } FastLED.show();
}

void loop() {
  if (irrecv.decode(&IR)) {                     // Hacemos lectura IR
    if ( IR.value == 0x1FE48B7 ){ btnIR = 1; }  // Identificamos botones
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
    irrecv.resume();
    selecColor(btnIR);    // Importante en decode para que el boton no quede siempre activo
    printLeds();
    delay(50);                                // Detectado debounce
  }


}


void selecColor(byte B){           // Seleccionamos el color(hue), la saturacion(sat) y el brillo(val) que
// Colores                         // queremos introducirle a los led seleccionados
// Rojo
  if (B == 3){
    if ( lastB == 8 ) { flagHue = 1; }  // Cambiamos valor con referencia,
    if ( lastB == 6 ) { flagHue = 0; }  // solo, a los colores continuos.

    if (valHue > 128 && valHue < 213) { valHue = 213; flagHue = 1;} // Acordamos los límites para aumentar
    else if (valHue < 128 && valHue > 43) { valHue = 43; flagHue = 0;}  // Acordamos los límites para disminuir

    else if (flagHue == 1) {            // Aumentamos valor
      if (valHue >= 255){ valHue = 0; } // Acordamos límite para invertir accion
      else { valHue = valHue + 1; }
    }
    else if (flagHue == 0) {            // Aumentamos valor
      if (valHue <= 0){ valHue = 255; } // Acordamos límite para invertir accion
      else { valHue = valHue - 1; }
    }
  }
// Amarillo
  if(B == 6) {
    if ( lastB == 3 ) { flagHue = 1; }
    if ( lastB == 4 ) { flagHue = 0; }

    if (valHue >= 170 || valHue < 0) { valHue = 0; flagHue = 1;}
    else if (valHue > 85 && valHue < 170) { valHue = 85; flagHue = 0;}

    else if (flagHue == 1) { valHue = valHue + 1; }
    else if (flagHue == 0) { valHue = valHue - 1; }
  }
//Verde
  if (B == 4){
    if ( lastB == 6 ) { flagHue = 1; }
    if ( lastB == 7 ) { flagHue = 0; }

    if (valHue < 43 || valHue >= 213) { valHue = 43; flagHue = 1;}
    else if (valHue < 213 && valHue > 128) { valHue = 128; flagHue = 0;}

    else if (flagHue == 1) { valHue = valHue + 1; }
    else if (flagHue == 0) { valHue = valHue - 1; }
  }
//Agua Marina
  if(B == 7) {
    if ( lastB == 4 ) { flagHue = 1; }
    if ( lastB == 5 ) { flagHue = 0; }

    if (valHue < 85) { valHue = 85; flagHue = 1;}
    else if (valHue > 170) { valHue = 170; flagHue = 0;}

    else if (flagHue == 1) { valHue = valHue + 1; }
    else if (flagHue == 0) { valHue = valHue - 1; }
  }
//Azul
  if (B == 5){
    if ( lastB == 7 ) { flagHue = 1; }
    if ( lastB == 8 ) { flagHue = 0; }

    if (valHue >= 43 && valHue < 128) { valHue = 128; flagHue = 1;}
    else if (valHue > 213 || valHue < 43) { valHue = 213; flagHue = 0;}

    else if (flagHue == 1) { valHue = valHue + 1; }
    else if (flagHue == 0) { valHue = valHue - 1; }
  }
//Purpura
  if (B == 8){
    if ( lastB == 5 ) { flagHue = 1; }
    if ( lastB == 3 ) { flagHue = 0; }

    if (valHue >= 85 && valHue < 170) { valHue = 170; flagHue = 1;}  // Valor extremo 1:=
    else if (valHue < 85) { valHue = 255; flagHue = 0;}

    else if (flagHue == 1) { valHue = valHue + 1; }
    else if (flagHue == 0) { valHue = valHue - 1; }
  }


// Sat Saturacion (Blanco ~ Color)
  if(B == 9) {
    if (valSat <= 9) { valSat = 0; }
    if (valSat > 9) { valSat = valSat - 10; }
  }
  if(B == 10) {
    if (valSat < 245) { valSat = valSat + 10; }
    if (valSat >= 245) { valSat = 255; }
  }

// Val Brillo (ON OFF)
  if(B == 1) {
    if (valVal <= 9) { valVal = 0; }
    if (valVal > 9) { valVal = valVal - 10; }
  }
  if(B == 2) {
    if (valVal < 245) { valVal = valVal + 10; }
    if (valVal >= 245) { valVal = 255; }
  }
  lastB = B;
}


void printLeds(){              /////    escribir solo si a cambiado algo
  if (valHue != lastValHue || valSat != lastValSat || valVal != lastValVal){
    for (int i = firstLed; i < lastLed; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
    FastLED.show();
    lastValHue = valHue, lastValSat = valSat, lastValVal = valVal;
  }
}
