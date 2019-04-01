#include <FastLED.h>
#define NUM_LEDS 32
#define DATA_PIN 11

#define COLOR_ORDER GRB
#define CHIPSET     WS2811

#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 30

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

CRGBPalette16 gPal;

int prevTime = 0;
int threshold = 1000;
int countdown = 0;

int counter = 0;
int counter2 = 0;
int counter3 = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);

  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  gPal = CRGBPalette16( CRGB::Black, CRGB::Purple, CRGB::Blue,  CRGB::White);
}

void loop() {

  int timer = millis();

  if (timer - prevTime >= threshold) {
    countdown = countdown + 1;
    prevTime = timer;
  }

  Serial.println(countdown);

  if (countdown >= 0 && countdown <=  8) {
    raindrop(5 * counter, 10 * counter, 20 * counter);
    counter = counter + 1;
  }
  else if (countdown > 8 && countdown <= 24) {
    raindrop(10 + 10 * counter2, 5 * counter2 + 30, 10 * counter2 + 50);
    counter2 = counter2 + 1;
  }
  else if (countdown > 24 && countdown <= 36) {
    dark_blue(10, 2, 25);
  }
  else if (countdown > 36 && countdown <= 44) {
    raindrop(150 +10 * counter3, 20 * counter3 + 40, 10 * counter3 + 100);
    counter3 = counter3 + 1;
  }
  else if (countdown > 44 && countdown <= 76) {
    Fire2012WithPalette();
  }
  else if (countdown > 76 && countdown <= 90) {
    reverseRaindrop( 5 * counter, 10 * counter, 20 * counter);
  }
  else {
    clearAllLEDs();
  }

  Serial.println("loop end");

}



void raindrop(int r, int g, int b) {

  for (int firstPix = 0; firstPix < NUM_LEDS + 5; firstPix++) {

    for (int i = 0; i < NUM_LEDS; i ++) {
      // turn off any LED that had color before
      leds[i].setRGB(0, 0, 0);

      // set the first pixel to the chosen color
      if (i == firstPix) {
        leds[i].setRGB(r, g, b);
      }

      // loop through the 1 to 3rd pixel before the firstPixel
      // and set them to an rgb color that's divided by j
      for (int j = 1; j < 4; j++) {
        int index = firstPix - j;
        if (i == index) {
          leds[i].setRGB(r / j, g / j, b / j);
        }
      }

    }

    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    //speed of one raindrop

  }
}

void reverseRaindrop(int r, int g, int b) {

  int trail = 5;
  //the length of the trail

  for (int firstPix = 32; firstPix > 0; firstPix--) {

    for (int i = 0; i < NUM_LEDS; i ++) {
      // turn off any LED that had color before
      leds[i].setRGB(0, 0, 0);

      // set the first pixel to the chosen color
      if (i == firstPix) {
        leds[i].setRGB(r, g, b);
      }

      // loop through the 1 to 3rd pixel before the firstPixel
      // and set them to an rgb color that's divided by j
      for (int j = trail; j > 0; j--) {
        int index = firstPix - j;
        if (i == index) {
          leds[i].setRGB(r / j, g / j, b / j);
        }
      }

    }

    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    //speed of one raindrop

  }
}

#define COOLING  55
#define SPARKING 120

void Fire2012WithPalette()
{

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


void clearAllLEDs() {
  for (int led = 0; led < NUM_LEDS; led ++) {
    leds[led].setRGB(0, 0, 0);
    FastLED.show();
  }
}

void dark_blue(int r, int g, int b) { //4秒每次
  for (int i = 0; i < NUM_LEDS; i ++) {
    leds[i] += CRGB(r, g, b);
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i --) {
    leds[i] += CRGB(r, g, b);
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}
