 /*
 * Led strip WS2815 control for IR
 *
 * State testing, developer c2mismo 2020.
 * License GNU, see at the end.
 */


#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE
#include <IRremote.h>

//Conf FstaLed
#define LED_PIN     5
#define NUM_LEDS    3
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2813
#define COLOR_ORDER         GRB

CRGB leds[NUM_LEDS];

int option;
byte led = 0;

//byte valHue = 128, valSat = 0, valVal = 0;
byte valHue = 0, valSat = 255, valVal = 25;
byte lastValHue = valHue, lastValSat = valSat, lastValVal = valVal;
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
  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
    for (int i = 0; i < NUM_LEDS; i = i + 1) { leds[i] = CHSV( valHue, valSat, valVal); } FastLED.show();
}

void loop() {
  if (paciFlag == 1){
    EVERY_N_MILLISECONDS( 20) {
      pacifica_loop();
    }
  }

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
      if (paciFlag){
        confPaciFlag = 0;
        valHue = lastValHue, valSat = lastValSat, valVal = lastValVal;
      }
      else {
        paciFlag = 1;
        lastValHue = valHue, lastValSat = valSat, lastValVal = valVal;
      }
      /////////////   sound
    }

    if (btnIR == 12){                         // Entramos en modo config Pacifica
      if (confPaciFlag){ confPaciFlag = 0; }
      else { confPaciFlag = 1; }
      /////////////   sound
    }

    if (btnIR == 13 && !sidesFlag){ sidesFlag = 1; }// Reset side        // Entramos en modo selections sides pero..
    if (sidesFlag && btnIR == 3){ sidesFlag = 3; }  // salimos con otro boton.

    if (!sidesFlag || !paciFlag || !confPaciFlag || btnIR == 11){
      ledWrite(btnIR);  // Debe de estar aqui adentro para poder mantener el boton pulsado
    }

    irrecv.resume();

  }


  if (!sidesFlag || !paciFlag || !confPaciFlag || btnIR == 11){
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



////////////////////////////////////////////////////////////////////////////////////// Pacific Control

CRGBPalette16 pacifica_palette_1 =
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
CRGBPalette16 pacifica_palette_2 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
CRGBPalette16 pacifica_palette_3 = 
    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };

      void pacifica_loop()
{
  // Increment the four "color index start" counters, one for each wave layer.
  // Each is incremented at a different speed, and the speeds vary over time.
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011,10,13));
  sCIStart2 -= (deltams21 * beatsin88(777,8,11));
  sCIStart3 -= (deltams1 * beatsin88(501,5,7));
  sCIStart4 -= (deltams2 * beatsin88(257,4,6));

  // Clear out the LED array to a dim background blue-green
  fill_solid( leds, NUM_LEDS, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301) );
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401) );
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503));
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  // Deepen the blues and greens a bit
  pacifica_deepen_colors();
}

// Add one layer of waves into the led array
void pacifica_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    leds[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );

  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = leds[i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      leds[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors()
{
  for( uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i].blue = scale8( leds[i].blue,  145);
    leds[i].green= scale8( leds[i].green, 200);
    leds[i] |= CRGB( 2, 5, 7);
  }
}
