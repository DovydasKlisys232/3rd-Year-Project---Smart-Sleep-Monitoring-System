/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This is the implementation of the screen.h header file. the display function is defined
  to display on the screen the collected readings from the DHT20.
*/

#include "Temp-Hum.h"
#include "screen.h"
#include <Arduino.h>

//initialize the lcd (cs, dc, mosi, sclk, rst)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK);

// Produces the initial display of the screen
void display(){
  tft.setTextSize(2);
  tft.setCursor(0, 0);

  tft.print("Temperature: ");
  tft.print("\n");

  tft.print("Humidity: ");
  tft.print("\n");

  tft.print("SPL: ");       // new label
  tft.print("\n");

}

// called to update the screen after new readings are collected
void update(float temp, float hum, float SPL, bool status){
  // Temperature value
  tft.fillRect(150, 0, 100, 30, ST77XX_BLACK); 
  tft.setCursor(150, 0);
  tft.print(temp, 2);
  tft.print("C"); 

  // Humidity value
  tft.fillRect(105, 16, 150, 30, ST77XX_BLACK);
  tft.setCursor(110, 17);
  tft.print(hum, 2);
  tft.print("%");

  // SPL value
  tft.fillRect(55, 32, 150, 30, ST77XX_BLACK);
  tft.setCursor(60, 33);
  tft.print(SPL, 2);
  tft.print("dB");

  status = true;
}