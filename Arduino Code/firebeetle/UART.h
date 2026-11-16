/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 25/3/26
  Purpose: This is the header file for the uart code. The esp32-c6 Firebeetle 2 will collect the SPL value from the esp32 classic.
*/

#pragma once

#include "Arduino.h"

// Define the RX and TX pins for Serial 2
#define RXD 6
#define TXD 7

#define BAUD 9600

// Create an instance of the HardwareSerial class for Uart
extern HardwareSerial mySerial;
