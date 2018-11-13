#include "Adafruit_NeoPixel.h"

#define PIXEL_PIN     D5
#define PIXEL_COUNT   24
#define PIXEL_TYPE    NEO_GRB + NEO_KHZ800
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int Shock = A0; 
int val;
void setup ()
{
pinMode(Shock, INPUT);
Serial.begin(115200);
Serial.println(analogRead(Shock));
Serial.println("hey");
 pixels.begin();
}
void loop ()
{ 
  Serial.println(Shock);
  delay(6000);
val = analogRead(Shock) ;
{
  if (val < 17){
 for(int i=0; i<PIXEL_COUNT; ++i) {
            pixels.setPixelColor(i, pixels.Color(0,255,0));
          }

         pixels.show();
}
else
{
 chase(pixels.Color(0, 0, 255)); // Blue

         
}
}
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<pixels.numPixels()+5; i++) {
      pixels.setPixelColor(i  , c); // Draw new pixel
      pixels.setPixelColor(i-5, 0); // Erase pixel a few steps back
      pixels.show();
      delay(35);
  }
}
