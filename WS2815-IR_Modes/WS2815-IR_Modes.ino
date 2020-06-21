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

//byte valHue = 128, valSat = 0, valVal = 0;
byte valHue = 0, valSat = 255, valVal = 25;
bool flagHue = 0;

//Conf IRremote
const byte RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results IR;
byte btnIR;
byte lastB;
bool paciFlag = 0, confPaciFlag = 0, sidesFlag = 0;
byte side = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  LEDS.addLeds<WS2813, LED_PIN, GRB>(leds, NUM_LEDS);
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

    if (btnIR == 11){                         // Entramos en modo config Pacifica
      if (paciFlag){ confPaciFlag = 0; }
      else { paciFlag = 1; }
      /////////////   sound
    }

    if (btnIR == 12){                         // Entramos en modo config Pacifica
      if (confPaciFlag){ confPaciFlag = 0; }
      else { confPaciFlag = 1; }
      /////////////   sound
    }

    if (btnIR == 13 && !sidesFlag){ sidesFlag = 1; // Reset side }        // Entramos en modo selections sides pero..
    if (sidesFlag && btnIR == 3){ sidesFlag = 3; }  // salimos con otro boton.

    if (!sidesFlag || !confPaciFlag || btnIR == 11){
      ledWrite(btnIR);  // Debe de estar aqui adentro para poder mantener el boton pulsado
    }

    irrecv.resume();
    delay(10);
  }


  if (!sidesFlag || !confPaciFlag || btnIR == 11){
    ledShow(btnIR);
  }


    FastLED.show();
}
// poner el automatico y comprobar el uso del boton pulsado



void ledShow(byte sides){           // Seleccionamos los led a los que vamos a cambiar el color
  for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); }
}




void ledWrite(byte B){           // Seleccionamos el color(hue), la saturacion(sat) y el brillo(val) que
                                 // queremos introducirle a los led seleccionados

// Rojo
  if (B == 3){
    if ( lastB == 8 ) { flagHue = 1; }  // Cambiamos valor con referencia,
    if ( lastB == 6 ) { flagHue = 0; }  // solo, a los botones continuos.

    if (valHue > 128 && valHue < 213) { valHue = 213; flagHue = 1;} // Acordamos los límites para aumentar
    else if (valHue < 128 && valHue > 43) { valHue = 43; flagHue = 0;}  // Acordamos los límites para disminuir

    else if (flagHue) {            // Aumentamos valor
      if (valHue >= 255){ valHue = 0; } // Acordamos límite para invertir accion
      else { valHue = valHue + 1; }
    }
    else if (!flagHue) {            // Aumentamos valor
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

    else if (flagHue) { valHue = valHue + 1; }
    else if (!flagHue) { valHue = valHue - 1; }
  }
//Verde
  if (B == 4){
    if ( lastB == 6 ) { flagHue = 1; }
    if ( lastB == 7 ) { flagHue = 0; }

    if (valHue < 43 || valHue >= 213) { valHue = 43; flagHue = 1;}
    else if (valHue < 213 && valHue > 128) { valHue = 128; flagHue = 0;}

    else if (flagHue) { valHue = valHue + 1; }
    else if (!flagHue) { valHue = valHue - 1; }
  }
//Agua Marina
  if(B == 7) {
    if ( lastB == 4 ) { flagHue = 1; }
    if ( lastB == 5 ) { flagHue = 0; }

    if (valHue < 85) { valHue = 85; flagHue = 1;}
    else if (valHue > 170) { valHue = 170; flagHue = 0;}

    else if (flagHue) { valHue = valHue + 1; }
    else if (!flagHue) { valHue = valHue - 1; }
  }
//Azul
  if (B == 5){
    if ( lastB == 7 ) { flagHue = 1; }
    if ( lastB == 8 ) { flagHue = 0; }

    if (valHue >= 43 && valHue < 128) { valHue = 128; flagHue = 1;}
    else if (valHue > 213 || valHue < 43) { valHue = 213; flagHue = 0;}

    else if (flagHue) { valHue = valHue + 1; }
    else if (!flagHue) { valHue = valHue - 1; }
  }
//Purpura
  if (B == 8){
    if ( lastB == 5 ) { flagHue = 1; }
    if ( lastB == 3 ) { flagHue = 0; }

    if (valHue >= 85 && valHue < 170) { valHue = 170; flagHue = 1;}  // Valor extremo 1:=
    else if (valHue < 85) { valHue = 255; flagHue = 0;}

    else if (flagHue) { valHue = valHue + 1; }
    else if (!flagHue) { valHue = valHue - 1; }
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
