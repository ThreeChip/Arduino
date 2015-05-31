/* SparkFun WS2812 Breakout Board Example
  SparkFun Electronics
  date: July 25, 2013
  license: GNU GENERAL PUBLIC LICENSE
  
  Requires the Adafruit NeoPixel library. It's awesome, go get it.
  https://github.com/adafruit/Adafruit_NeoPixel
  
  This simple example code runs three sets of animations on a group of WS2812
  breakout boards. The more boards you link up, the better these animations
  will look. 
  
  For help linking WS2812 breakouts, checkout our hookup guide:
  https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide
  
  Before uploading the code, make sure you adjust the two defines at the
  top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
  you've got connected to the first pixel's DIN pin. By default it's
  set to Arduino pin 4. LED_COUNT should be the number of breakout boards
  you have linked up.
*/
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 2
#define LED_COUNT 42
long colorOne = YELLOW;
long colorTwo = ORANGE;
long colorThree = GREEN;

int randNumber = 0;
int randLED1 = 0;
int randLED2 = 0;
int randLED3 = 0;
int randColor = 0;
long incomingByte = 0;
long mode = 2;
long count;
const int buttonPin = 12;     // the number of the pushbutton pin
int lastButtonState = 0;
int buttonState = 0;
int buttonPushCounter = 0;

// Create an instance of the Adafruit_NeoPixel class called "leds".
// That'll be what we refer to from here on...
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.setPixelColor(0, GREEN);
  leds.show();   // ...but the LEDs don't actually update until you call this.   
  pinMode(buttonPin, INPUT); 
   Serial.begin(9600);
}


void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}


void loop ()
{

  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;

  modechange();

  if (mode == 0) {     
  clearLEDs();
  leds.show();
  }
  else if (mode == 1) {
  dimred();
  }
  else if (mode == 2) {
colorOne = YELLOW;
colorTwo = GREEN;
colorThree = ORANGE;
  slowstrobe();
  }
  else if (mode == 3) {
colorOne = YELLOW;
colorTwo = GREEN;
colorThree = ORANGE;
  faststrobe();
  }
  else if (mode == 4) {
colorOne = YELLOW;
colorTwo = GREEN;
colorThree = ORANGE;

  faststrobe();

  }
  else if (mode == 5) {
colorOne = WHITE;
colorTwo = WHITE;
colorThree = WHITE;
  faststrobe();
  }
  else if (mode == 6) {
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0xFFFFFF);
    leds.show();
  }
  }

if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
char incomingChar=char(incomingByte);               
mode = incomingChar;
                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingChar);
                 Serial.print("Mode: ");
                Serial.println(mode);
               
                leds.show();
        }

}

void dimred()
{
 
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0x050000);
  }
  leds.show();
  
}

void slowstrobe()
{
  
  randLED1 = random(0,42);
  randLED2 = random(0,42);
  randLED3 = random(0,42);
  
  leds.setPixelColor(randLED1, colorOne);
  leds.setPixelColor(randLED2, colorTwo);
  leds.setPixelColor(randLED3, colorThree);
  leds.show();
  delay(50);
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0x100000);
  }
  leds.show();
  
}

void faststrobe()
{
  
  randLED1 = random(0,42);
  randLED2 = random(0,42);
  randLED3 = random(0,42);
  
  randColor = random(1,4);
  
  leds.setPixelColor(randLED1, colorOne);
  leds.setPixelColor(randLED2, colorTwo);
  leds.setPixelColor(randLED3, colorThree);
  leds.show();
  delay(3);
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0x050000);
  }
  leds.show();
  
}

void modechange()
{
   
buttonState = digitalRead(buttonPin);

if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
     if (mode >= 6) {
      mode = 0;
     }
     else
     { 
      mode++;
     }
      Serial.println("Mode Change");
      Serial.print("Current Mode:  ");
      Serial.println(mode);
    } 
  }
}

