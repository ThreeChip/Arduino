#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN1 2
#define COUNT1 35
#define PIN2 3
#define COUNT2 13
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
long mode = 1;
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
   topsolidsideblink();
  modechange();

  if (mode == 0) {     
  clearLEDs();
  showLEDs();
  }
  else if (mode == 1) {
    toponlysolid();
    
  }
  else if (mode == 2) {
    alternate();

  }
  else if (mode == 3) {
    dimred();
  }
  else if (mode == 4) {
    fullred();


  }
  else if (mode == 5) {
colorOne = YELLOW;
colorTwo = YELLOW;
colorThree = YELLOW;
  slowstrobe();
  }
  else if (mode == 6) {
  for (int i=0; i<COUNT2; i++)
  {
    led1.setPixelColor(i, 0xFFFFFF);
    showLEDs();
  }
  }
}

void topsolid()
{
  
    for (int i=0; i<COUNT2; i++)
  {
    led2.setPixelColor(i, 0xFF0000);
  }
  
}

void topsolidsideblink()
{
      for (int i=2; i<11; i++)
  {
    led2.setPixelColor(i, 0x220000);
  }
  int tssbpreviousMillis = 0;
  long tssbinterval = 5000;  
  int tssbState = LOW; 
  if(millis() - tssbpreviousMillis > tssbinterval) {
    // save the last time you blinked the LED 
  
      Serial.print("\n");
      Serial.println(tssbpreviousMillis);
      Serial.println(millis());
          tssbpreviousMillis = millis(); 
    // if the LED is off turn it on and vice-versa:
    if (tssbState == LOW){
    led2.setPixelColor(0, 0xFF0000);
    led2.setPixelColor(1, 0x000000);
    led2.setPixelColor(11, 0x000000);
    led2.setPixelColor(12, 0xFF0000);
    showLEDs();
    tssbState = HIGH;
    } else {
    led2.setPixelColor(0, 0x000000);
    led2.setPixelColor(1, 0xFF0000);
    led2.setPixelColor(11, 0xFF0000);
    led2.setPixelColor(12, 0x000000);
    tssbState = LOW;
    showLEDs();
  }

  
}
}

void toponlysolid()
{
  
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0);
  }
  
     for (int i=11; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
  led1.setPixelColor(1, 0xFF0000);
  led1.setPixelColor(33, 0xFF0000);
  
  showLEDs();
}
void alternate()
{
 clearLEDs();
  
     for (int i=10; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
  
  
    for (int i=0; i<11; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
    for (int i=24; i<36; i++)
  {
    led1.setPixelColor(i, 0x440000);
  }
  showLEDs();
  delay(250);
      for (int i=0; i<11; i++)
  {
    led1.setPixelColor(i, 0x440000);
  }
    for (int i=24; i<36; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
  showLEDs();
  delay(250);
  
}

void dimred()
{
 
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x500000);
  }
  showLEDs();
  
}

void fullred()
{
 
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
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
       for (int i=10; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
  showLEDs();
  delay(75);
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x500000);
  }
       for (int i=10; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
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
       for (int i=10; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
  }
  showLEDs();
  delay(10);
  for (int i=0; i<COUNT1; i++)
  {
    led1.setPixelColor(i, 0x500000);
  }
       for (int i=10; i<24; i++)
  {
    led1.setPixelColor(i, 0xFF0000);
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

