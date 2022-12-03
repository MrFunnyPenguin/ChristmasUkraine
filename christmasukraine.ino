#include <FastLED.h>

FASTLED_USING_NAMESPACE
#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    150


#define FRAMES_PER_SECOND 120

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

void setup() {
  delay(4000); 
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);


  Serial.begin(57600);
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { gold, ukraine, christmas, redwhite, hanukah, bpm, rainbow, rainbowWithGlitter, glitter, sinelon };

uint8_t gCurrentPatternNumber = 0; 
uint8_t gHue = 0; 

void loop()
{

  
  gPatterns[gCurrentPatternNumber]();
  FastLED.show();  
  
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  

  EVERY_N_MILLISECONDS( 5 ) { gHue++; } //for rainbow
  EVERY_N_SECONDS( 25 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void ukraine()
{
uint16_t sinBeat = beatsin16(12, 0, NUM_LEDS - 1, 0, 0);
 uint16_t sinBeat2 = beatsin16(12, 0, NUM_LEDS - 1, 0, 85);

 

 leds[sinBeat] = CRGB::CRGB(200,200,0);
 leds[sinBeat2] = CRGB::CRGB(0,60,255);
 
 fadeToBlackBy(leds, NUM_LEDS, 3);

}

void christmas()
{
uint16_t sinBeat = beatsin16(12, 0, NUM_LEDS  -1, 0, 0);
uint16_t sinBeat2 = beatsin16(12, 0, NUM_LEDS -1, 0, 100);
uint16_t sinBeat3 = beatsin16(12, 0, NUM_LEDS  -1, 0, 0);
uint16_t sinBeat4 = beatsin16(12, 0, NUM_LEDS -1, 0, 100);


 leds[sinBeat] = CRGB::CRGB(0,255,0);
 leds[sinBeat2] = CRGB::CRGB(255,0,0);
 leds[sinBeat3] = CRGB::CRGB(0,255,0);
 leds[sinBeat4] = CRGB::CRGB(255,0,0);

 
 
 fadeToBlackBy(leds, NUM_LEDS, 3);

 EVERY_N_MILLISECONDS(25){
      Serial.print(sinBeat);
      Serial.print(",");
      Serial.print(sinBeat2);
      Serial.print(",");  
      Serial.print(sinBeat3);
      Serial.print(",");   
      Serial.print(sinBeat4);
      Serial.print(",");            
    }

    FastLED.show();

}

void redwhite()
{
uint16_t sinBeat = beatsin16(12, 0, NUM_LEDS  -1, 0, 0);
uint16_t sinBeat2 = beatsin16(12, 0, NUM_LEDS -1, 0, 100);


 leds[sinBeat] = CRGB::CRGB(255,255,255);
 leds[sinBeat2] = CRGB::CRGB(255,0,0);

 
 
 fadeToBlackBy(leds, NUM_LEDS, 1);

 EVERY_N_MILLISECONDS(25){
      Serial.print(sinBeat);
      Serial.print(",");
      Serial.print(sinBeat2);
      Serial.print(",");            
    }

    FastLED.show();

}

void gold()
{
uint16_t sinBeatG = beatsin16(15, 0, NUM_LEDS  -1, 0, 0);


 leds[sinBeatG] = CRGB::CRGB(245,218,36);


 
 
 fadeToBlackBy(leds, NUM_LEDS, 9);

 EVERY_N_MILLISECONDS(25){
      Serial.print(sinBeatG);
      Serial.print(",");          
    }

    FastLED.show();

}

void hanukah()
{
uint16_t sinBeat = beatsin16(12, 0, NUM_LEDS  -1, 0, 0);
uint16_t sinBeat2 = beatsin16(12, 0, NUM_LEDS -1, 0, 100);


 leds[sinBeat] = CRGB::CRGB(255,255,255);
 leds[sinBeat2] = CRGB::CRGB(0,0,255);

 
 
 fadeToBlackBy(leds, NUM_LEDS, 3);

 EVERY_N_MILLISECONDS(25){
      Serial.print(sinBeat);
      Serial.print(",");
      Serial.print(sinBeat2);
      Serial.print(",");            
    }

    FastLED.show();

}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void glitter()
{
  // a colored dot sweeping back and forth, with fading trails
  addRGlitter(80);
  addGGlitter(80);
  addGOGlitter(80);
  fadeToBlackBy( leds, NUM_LEDS, 20);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void addRGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::Red;
  }
}

void addGGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::Green;
  }
}
void addGOGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::Yellow;
  }
}


