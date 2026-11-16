/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This is the header file for the tft screen. This will define the pin connections, declare necessary functions for the screen and 
  any objects.
*/

#pragma once

#include <Adafruit_ST7789.h>  // library for the screen

//define pins on LCD screen
#define TFT_DC 8
#define TFT_CS 14
#define TFT_MOSI 22
#define TFT_SCLK 23
#define TFT_RST -1 //set to default

// tft screen object decleration
extern Adafruit_ST7789 tft;

void display();
void update(float temp, float hum, float SPL, bool status);