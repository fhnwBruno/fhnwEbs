// I2C device class (I2Cdev) demonstration Arduino sketch for HMC5883L class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2013-05-04 - Added Heading Calculation in degrees
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and HMC5883L must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "HMC5883L.h"
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>


// class default I2C address is 0x1E
// specific I2C addresses may be passed as a parameter here
// this device only supports one I2C address (0x1E)
#define LCDADDR 0x20    // Adress for LCD display
#define LCDCOLS 16      // Number of coloums on LCD
#define LCDROWS 2     // Number of rows on LCD
#define TONEPIN 16
#define LEDPIN 10

// Defines für Motor control
#define FORW 0
#define BACK 1
// Defines der Motor Steuerpins
#define SpeedPinRight 6//pin for run the right motor 
#define DirectionRight 7//pin for control right motor direction
#define SpeedPinLeft 5//pin for run the left motor 
#define DirectionLeft 12//pin for control left motor direction
// Define für Geschwindigkeit
#define SPEEDMAX 255


HMC5883L mag;
LiquidCrystal_I2C lcd (LCDADDR, LCDCOLS, LCDROWS);
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, LEDPIN, NEO_GRB + NEO_KHZ800);
int16_t mx, my, mz;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    delay(1000);
    lcd.begin();
    lcd.backlight();
    led.begin();
    led.show(); // Initialize all pixels to 'off'
    pinMode(TONEPIN, OUTPUT);
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    mag.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");

    
  pinMode(5,OUTPUT);//init the motor driver pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  
}

void loop() {
    // read raw heading measurements from device
    mag.getHeading(&mx, &my, &mz);
    //mx = mx - (-326); //Brugg Projektraum
    //my = my - 288; //Brugg Proejktraum
    mx = mx - 291; //Brugg Projektraum
    my = my - 321; //Brugg Proejktraum
    
    // display tab-separated gyro x/y/z values
    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.print(mz); Serial.print("\t");
    
// To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(my, mx);
    // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (2.0 + (16.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

    if(heading < 0)      {heading += 2 * M_PI;}
    heading = heading * 180/M_PI;
    Serial.print("heading:\t");
    Serial.println(heading);
    lcd.clear();
    lcd.print(heading);
    /*
    //rot= 180, gelb= 90 oder 255, grün= 0 oder 360
    if(heading < 90){
      led.setPixelColor(0, map(heading, 0, 89, 0, 255), 255, 0);
      led.show();
    }
    if(heading >= 90 && heading <= 180){
      led.setPixelColor(0, 255, map(heading, 90, 180, 255, 0), 0);
      led.show();
    }
    if(heading > 180 && heading <= 255){
      led.setPixelColor(0, 255, map(heading, 181, 255, 0, 255), 0);
      led.show();
    }  
    if(heading > 255){
      led.setPixelColor(0, map(heading, 256, 360, 255, 0), 255, 0);
      led.show();
    }*/   

    //Make tones & light effects
    if(heading > 350 || heading < 10)
    {
      setTurn(0, 0);
      tone(TONEPIN,100);
    }else
    {
      setTurn(-1, 100);
      noTone(TONEPIN);
    }
        
    delay(100);
    
}

void setTurn(int angle, int turnspeed)
{
  if (angle < 0) 
  {
    // Rechtsdrehen
    digitalWrite(DirectionRight, FORW);
    digitalWrite(DirectionLeft, BACK);
    analogWrite(SpeedPinRight, turnspeed);
    analogWrite(SpeedPinLeft, turnspeed);
  }
  if(angle==0)
  {
    analogWrite(SpeedPinRight, LOW);
    analogWrite(SpeedPinLeft, LOW);
  }
  else
  {
    // Linksdrehen
    digitalWrite(DirectionRight, BACK);
    analogWrite(SpeedPinRight, turnspeed);
    digitalWrite(DirectionLeft, FORW);
    analogWrite(SpeedPinLeft, turnspeed);
  }
}
