#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN1 2
#define COUNT1 34
#define PIN2 3
#define COUNT2 42
#define PIN3 4
#define COUNT3 42


long colorOne = YELLOW;
long colorTwo = ORANGE;
long colorThree = GREEN;

int randNumber = 0;
int randLED1 = 0;
int randLED2 = 0;
int randLED3 = 0;
int randColor = 0;
long incomingByte = 0;
long mode = 0;
long count;
const int buttonPin = 12;     // the number of the pushbutton pin
int lastButtonState = 0;
int buttonState = 0;
int buttonPushCounter = 0;

Adafruit_NeoPixel led1 = Adafruit_NeoPixel(COUNT1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led2 = Adafruit_NeoPixel(COUNT2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led3 = Adafruit_NeoPixel(COUNT3, PIN3, NEO_GRB + NEO_KHZ800);

void setup()
{
  led1.begin();  // Call this to start up the LED strip.
  led2.begin();
  led3.begin();
  clearLEDs();   // This function, defined below, turns all LEDs off...
  led1.show();
  led2.show();
  led3.show(); 
  pinMode(buttonPin, INPUT); 
   Serial.begin(9600);
}


void clearLEDs()
{
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0);
  }
    for (int i=0; i<COUNT2; i++)
  {
    led2.setPixelColor(i, 0);
  }
    for (int i=0; i<COUNT3; i++)
  {
    led3.setPixelColor(i, 0);
  }
}

void showLEDs()
{
 
  led1.show();
  led2.show();
  led3.show();
  
}

void loop ()
{

  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;

  modechange();

  if (mode == 0) {     
  clearLEDs();
  showLEDs();
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

  alternate();

  }
  else if (mode == 5) {
colorOne = WHITE;
colorTwo = WHITE;
colorThree = WHITE;
  faststrobe();
  }
  else if (mode == 6) {
  for (int i=0; i<COUNT2; i++)
  {
    led2.setPixelColor(i, 0xFFFFFF);
    showLEDs();
  }
  }
}

void alternate()
{
 
    for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
    for (int i=0; i<COUNT2; i++)
  {
    led2.setPixelColor(i, 0x440000);
  }
  showLEDs();
  delay(250);
      for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x440000);
  }
    for (int i=0; i<COUNT2; i++)
  {
    led2.setPixelColor(i, 0xFF0000);
  }
  showLEDs();
  delay(250);
  
}

void dimred()
{
 
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x050000);
  }
  showLEDs();
  
}

void slowstrobe()
{
  
  randLED1 = random(0,42);
  randLED2 = random(0,42);
  randLED3 = random(0,42);
  
  led1.setPixelColor(randLED1, colorOne);
  led1.setPixelColor(randLED2, colorTwo);
  led1.setPixelColor(randLED3, colorThree);
  showLEDs();
  delay(50);
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x100000);
  }
  showLEDs();
  
}

void faststrobe()
{
  
  randLED1 = random(0,42);
  randLED2 = random(0,42);
  randLED3 = random(0,42);
  
  randColor = random(1,4);
  
  led1.setPixelColor(randLED1, colorOne);
  led1.setPixelColor(randLED2, colorTwo);
  led1.setPixelColor(randLED3, colorThree);
  showLEDs();
  delay(3);
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x050000);
  }
  showLEDs();
  
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

