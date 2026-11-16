/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This is the implementation of the Temp-Hum.h file. this code includes two functions for reading
  the temperature and humidity from the sensor. It also includes the fan code to decide an outcome
  based on the temperature reading and comparing it with the threshold value.
*/

#include "Temp-Hum.h"
#include <Arduino.h>

DHT20 DHT(&Wire);

// this function checks the status of the sensor
void check_stats(int status){
  switch (status)
  {
  case DHT20_OK:
    Serial.println("DHT: OK");
    break;
  case DHT20_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case DHT20_ERROR_CONNECT:
    Serial.print("Connect error,\t");
    break;
  case DHT20_MISSING_BYTES:
    Serial.print("Missing bytes,\t");
    break;
  case DHT20_ERROR_BYTES_ALL_ZERO:
    Serial.print("All bytes read zero");
    break;
  case DHT20_ERROR_READ_TIMEOUT:
    Serial.print("Read time out");
    break;
  case DHT20_ERROR_LASTREAD:
    Serial.print("Error read too fast");
    break;
  default:
    Serial.print("Unknown error,\t");
    break;
  }
}

