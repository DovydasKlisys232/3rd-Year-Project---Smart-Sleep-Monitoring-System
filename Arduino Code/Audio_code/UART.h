/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 25/3/26
  Purpose: This is the header file for the uart code. the esp32 classic will send out its data to the esp32-C6 firebeetle 2 and this esp module will 
  do its own processing and displays the other's data.
*/

#pragma once

// Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600

// Create an instance of the HardwareSerial class for Serial 2
extern HardwareSerial mySerial(2);
