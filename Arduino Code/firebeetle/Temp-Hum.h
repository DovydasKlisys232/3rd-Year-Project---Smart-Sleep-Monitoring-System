/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This is the header file for the DHT20 code. It ensures that the i2c protocol is initialized properly and that the 
  sensor can collect temperature and humidity readings properly.
*/

#pragma once

#include <Wire.h>               //essential library for i2c protocol
#include <DHT20.h>              // library for DHT20

#define SDA_PIN 19
#define SCL_PIN 20

extern float temperature;
extern float humidity;

extern DHT20 DHT;

void check_stats(int status);