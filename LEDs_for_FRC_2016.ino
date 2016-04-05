#include <Wire.h>
#include "FastLED.h"

#define NUM_LEDS 60
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

int color;
int effect;
boolean fadding = true;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Hello");
  delay(2000);

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);

  // Make effects happen
  if (effect == 1) {
    // If fadding = true, fade from white to black
    if (fadding == true) {
      for (int brightness = 255; brightness > 0; brightness++) {
        for (int index = 0; index <= (nrOfLEDs - 1); index++) {
          leds[i].setHSV(HSV[0], HSV[1], brightness);
        }
        FastLED.show(); //Update LED display
      }
      fadding = false;
    }
    // Otherwise fade from black to white
    else {
      for (int brightness = 0; brightness <= 255; brightness++) {
        for (int index = 0; index <= (nrOfLEDs - 1); index++) {
          leds[i].setHSV(HSV[0], HSV[1], brightness);
        }
        FastLED.show(); //Update LED display
      }
      fadding = true;
    }
  }

  FastLED.show();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  String LED = "";

  while ( Wire.available() > 0 ) {
    char n = (char)Wire.read();
    if (((int)n) > ((int)(' ')))
      LED += n;
  }
  Serial.print(LED);

  // Determine color
  if (LED.indexOf("r") != -1) {
    color = 1;
  }
  else {
    color = 2;
  }

  // Get effect
  if (LED.indexOf("t") != -1) {
    effect = 1;
  }
  if (LED.indexOf("s") != -1) {
    effect = 2;
  }
  if (LED.indexOf("f") != -1) {
    effect = 3;
  }
  if (LED.indexOf("b") != -1) {
    effect = 4;
  }
}
