# Tsunami early warning system (IOT manual)

## In this manual
  [Introduction](#introduction)
  
  [Components](#components) 
  
  [Step 1: Connecting the hardware](#step-1-connecting-the-hardware) 
  
  [Step 2: Testing the sensor](#step-2-testing-the-sensor)
  
  [Step 3: Testing the ledstrip](#step-3-testing-the-ledstrip)
  
  [Step 4: Setting up the code](#step-4-setting-up-the-code)
  
  [Step 5: The early warning system](#step-5-the-early-warning-system)
  
  [Step 6: All Done](#step-6-all-done)
  
## Introduction

In this manual I'm going to show you how to make a (very rudimentary) Tsunami early warning system. It uses a vibration sensor that has a spring when the spring shakes it outputs a value that we can use to control an LED strip  All the code is written on MacOS and with the Arduino IDE program. 
You can download the Arduino IDE here: https://www.arduino.cc/en/Main/Software

## Components:
For this manual you'll need the following components:

  - NodeMCU V3
  - KY-002 vibration sensor
  - 6 female to female wires
  - Neopixel Ledstrip ws2812b
  - Micro usb cable

## Step 1 Connecting the hardware

![Fritzing Tsunami early warning system](https://raw.githubusercontent.com/pepijnlauriks/IOT/master/IOTfritzing.png)

Connect the hardware components by following this diagram


## Step 2 Testing the sensor
If everything is wired up we can try getting a value from our sensor. We'll need to read the value of A0 using analogRead to get a value between 0 and 1024. And we want to print that value in our serial monitor using:
```
Serial.println(analogRead(A0));
```
Don't forget to use Serial.begin in you're code otherwise nothing will happen in your serial monitor.

Now when you give the sensor a good smack you can see the value go up like in the picture below.
![Sensor value in serial monitor](https://raw.githubusercontent.com/pepijnlauriks/IOT/master/Checkpointsensor.png)

If it's not working make sure the sensor is connected like the diagram at [Step 1: Connecting the hardware](#step-1-connecting-the-hardware).

## Step 3 Testing the ledstrip
Before we can use the ledstrip we'll have to install the Neopixel library in Arduino IDE. 
You can do that by going to Tools > Manage Libraries... in arduino IDE and then you can type in Adafruit Neopixel and you should see the following:
![Sensor value in serial monitor](https://raw.githubusercontent.com/pepijnlauriks/IOT/master/neopixellibrary.png)
Click install!
Once installed we can try the example called 'simple' under File > Examples > Adafruit Neopixel and see if the ledstrip works. Make sure to change the pin to D5 before uploading. Your leds should light up green if everything works correctly. If it's not working make sure the ledstrip is connected like the diagram at [Step 1: Connecting the hardware](#step-1-connecting-the-hardware) and that you changed the pin to D5.

## Step 4 Setting up the code
Now we can start making our early warning system. First of we'll take some code frome the simple example so that we can use our ledstrip
```
#include <Adafruit_NeoPixel.h>

#define PIN           D5
#define NUMPIXELS     10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
```
After that we'll make a variable using ```int``` to define our A0 pin. I called the variable Shock. And a variable to read out the value of our sensor using ```analogRead(Shock)``` I called the variable Value.

Now in the void setup() we'll define our input and output using pinMode
```
pinMode(Shock, INPUT);
pinMode(D5, OUTPUT);
```
and use  ```pixels.begin();``` to initializes the NeoPixel library.

## Step 5 The early warning system
In the loop we'll make an IF-statement to trigger our leds when our sensor value goes up.
to see what you value you should use as threshold you can use ```Serial.println(analogRead(A0));``` again to decide how sensitive you want your system to be. I'm using a value of 17.
So if our variable Value is less(<) than 17 we want everyone to know that they dont have to worry about a tsunami.
We'll do that by take some code from the 'simple' example again, telling everyone everything is fine with a green light.
```
for(int i=0; i<NUMPIXELS; ++i) {
            pixels.setPixelColor(i, pixels.Color(0,255,0));
          }

         pixels.show();
```
and then if its something else it's going to be dangerous so we should give feedback that people should evacuate. so using an else statement we're going to make a light trail to safety for this I used some code I found on https://learn.adafruit.com/neopixel-painter/test-neopixel-strip which gives us a cool trailing light animation.
### Outside of the loop
We're going to make a function chase using the following code
```
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}
```
Now we can call this function in the else statement inside the loop and give it the color we want using ```pixels.color```

## Step 6 All Done
Congratulations! You should now have the most basic tsunami early warning system ever. If it's still not working you can try downloading my code and seeing if it works then, the sensor or ledstrip might just be broken.
