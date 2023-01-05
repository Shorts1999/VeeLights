#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_AMOUNT  50
#define LED_PIN     6

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_AMOUNT, LED_PIN, NEO_RGB | NEO_KHZ800);

#define BREATHING_COUNT 15                                            //Amount of LEDs affected by the brightness change
#define MINIMUM_VALUE   20                                            //Lowest brightness value to go down to
#define VALUE_MULT_BASE ((255-MINIMUM_VALUE) / (BREATHING_COUNT/2))   //Multiplier to reach minimum value evenly accross "BREATHING COUNT" amount of LEDs
#define HSV_MULTIPLIER 65535 / LED_AMOUNT                             //Divide 65535 by amount of LEDs to let rainbow fit exactly on strip

#define RED 0xff0000
#define BLUE 0x0000ff
#define GREEN 0x00ff00
#define MAGENTA 0xff00ff
#define CYAN 0x00ffff
#define YELLOW 0xffff00
#define BLACK 0x000000
#define WHITE 0xffffff
#define ORANGE 0xff6600

#define TEAL 0x006666

uint32_t colorList[] = {
  TEAL,
  MAGENTA,
  CYAN,
  RED,
  BLUE,
  WHITE,
  GREEN,
  MAGENTA,
  BLUE,
  CYAN
};

void setup() {
  leds.begin();
  leds.setBrightness(255);
  leds.clear();
  leds.show();

  // leds.setPixelColor(0, 0xff0000);
  // leds.setPixelColor(LED_AMOUNT - 1, 0x00ff00);
  // leds.show();
  // delay(1000);

  // leds.setPixelColor(2, MAGENTA);
  // leds.setPixelColor(3, ORANGE);
  // leds.setPixelColor(4, YELLOW);
  // leds.setPixelColor(5, GREEN);
  // leds.setPixelColor(6, BLUE);
  // leds.setPixelColor(7, BLACK);
  // leds.setPixelColor(8, WHITE);
  // leds.setPixelColor(27, TEAL);
  // leds.setPixelColor(9, RED);
  // leds.setPixelColor(10, ORANGE);
  // leds.setPixelColor(11, YELLOW);
  // leds.setPixelColor(12, GREEN);
  // leds.setPixelColor(13, TEAL);
  // leds.setPixelColor(14, BLUE);
  // leds.setPixelColor(15, BLACK);
  // leds.setPixelColor(16, WHITE);
  // leds.show();

  // leds.show();
  // delay(1000);

  // // leds.setPixelColor(41, 0xff99ff);
  // // leds.setPixelColor(17, 0x6600ff);
  // leds.show();
  // delay(1000);

  // leds.setPixelColor(12, RED);
  // leds.setPixelColor(13, TEAL);
  // leds.show();
  // delay(1000);


  for (uint16_t i = 0; i < LED_AMOUNT; i++) {
    leds.setPixelColor(i, leds.ColorHSV(HSV_MULTIPLIER * i));;
    leds.show();
    delay(40);
  }
}


void loop() {
  for (uint16_t i = 0; i < LED_AMOUNT; i++) {

    for (uint16_t j = 0; j < BREATHING_COUNT; j++) {
      //Use ternary statement (a ? b : c) to check for overflows
      uint16_t offset = (i + j) < LED_AMOUNT ? (i + j) : (i + j - LED_AMOUNT);
      uint16_t valueMultiplier = j < BREATHING_COUNT / 2 ? j : BREATHING_COUNT - j;
      leds.setPixelColor(offset, leds.ColorHSV(HSV_MULTIPLIER * offset, 255, 255 - (VALUE_MULT_BASE * valueMultiplier)));
    }

    leds.show();
    delay(150);

  }
}