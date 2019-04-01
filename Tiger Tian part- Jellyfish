#include <FastLED.h>
#define NUM_LEDS 30
#define DATA_PIN 11
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {

  // 0:00 - 0:16
  for (int i = 0; i < 4; i ++) {
    int i1 = i + 1;
    waves(10 * i1, 20 * i1, 40 * i1);
    clearAllLEDs();
    delay(2000);
  }

  // 0:16 - 0:32
  for (int i = 0; i < 8; i ++) {
    waves(20 * i + 10, 10 * i + 30, 25 * i + 50);
  }

  clearAllLEDs();

  //0:32 - 0:48
  for (int i = 0; i < 2; i ++) {
    dark_blue(10, 2, 25);
  }
  for (int i = 0; i < 2; i ++) {
    dark_blue(1, 20, 35);
  }
  clearAllLEDs();

  //0:48 - 1:20
  for (int i = 0; i < 16; i ++) {
    drumbeat(80 - i * 5, 90 - i * 5, 95 + i * 10);
  }
  for (int i = 0; i < 16; i ++) {
    drumbeat(10 + i * 7, 10 + i * 7, 95 + i * 10);
  }

  //1:20 - 1:52
  for (int i = 0; i < 16; i ++) {
    waves(20 * i + 10, 10 * i + 30, 25 * i + 50);
  }

  //1:52 - 2:08
  for (int i = 0; i < 3; i ++) {
    dark_blue(10, 20, 60);
  }

  //ending
  for (int i = 255; i >= 0; i -= 2) {
    for (int led = 0; led < NUM_LEDS; led ++) {
      leds[led] -= CRGB(1, 1, 1);
      FastLED.show();
    }
  }
  delay(60000);

}

void clearAllLEDs() {
  for (int led = 0; led < NUM_LEDS; led ++) {
    leds[led].setRGB(0, 0, 0);
    FastLED.show();
  }
}

void allLEDsSameColor(int r, int g, int b) {
  for (int led = 0; led < NUM_LEDS; led ++) {
    leds[led].setRGB(r, g, b);
  }
  FastLED.show();
}

void waves(int r, int g, int b) { //2秒每次
  for (int firstPix = 0; firstPix < NUM_LEDS + 5; firstPix++) {
    for (int i = 0; i < NUM_LEDS; i ++) {
      leds[i].setRGB(0, 0, 0);
      if (i == firstPix) {
        leds[i].setRGB(r, g, b);
      }
      for (int j = 1; j < 6; j ++) {
        int index = firstPix - j;
        if (i == index) {
          leds[i].setRGB(r / j, g / j, b / j);
        }
      }
    }
    FastLED.show();
    delay(2000 / (NUM_LEDS + 5));
  }
}

void dark_blue(int r, int g, int b) { //4秒每次
  for (int i = 0; i < NUM_LEDS; i ++) {
    leds[i] += CRGB(r, g, b);
    FastLED.show();
    delay(2000 / NUM_LEDS);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i --) {
    leds[i] += CRGB(r, g, b);
    FastLED.show();
    delay(2000 / NUM_LEDS);
  }
}

void drumbeat(int r, int g, int b) { //1秒每次
  int height = 20;
  for (int i = 0; i < height; i ++) {
    leds[i].setRGB(r / height * (height - i), g / height * (height - i), b / height * (height - i));
  }
  FastLED.show();

  for (int i = height - 1; i >= 0; i --) {
    leds[i].setRGB(0, 0, 0);
    FastLED.show();
    delay(500 / 20);
  }
  delay(470);
}
