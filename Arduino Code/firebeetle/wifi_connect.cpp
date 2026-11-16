/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This file defines wifi connection, mqtt and thingsboard connection code.
  It provides the necessary functions to connect to wifi and thingsboard as well as sending
  out data to thingsboard through mqtt.
*/

#include <Arduino.h>
#include "wifi_connect.h"

// initialize a wifi connection with correct credidentials
void initWifi(){
  //inform on serial monitor that trying to connect to wifi
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  //starts a wifi connection with credidentials
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  //wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
  } 
  else {
    Serial.println("\nWiFi FAILED — running offline");
  }
}

//check if thingsboard connection is ok
void check_thingsboard()
{
  //check if thingsboard is not connected
  if (!tb.connected()) {
    Serial.print("Connecting to ThingsBoard: ");
    Serial.println(TB_SERVER);

    //if the connect function came out true then display to monitor that connection is ok
    if (tb.connect(TB_SERVER, TB_TOKEN, TB_PORT)) {
      Serial.println("Connected to ThingsBoard!");
    } 
    //else the connection failed and need to try again
    else {
      Serial.println("Connection failed");
    }

  }
}

// send data from esp to thingsboard
void publishTelemetry(float temp, float hum, float spl, bool status){
  if (!tb.connected()) return;

  if(status == true){
    tb.sendTelemetryData(TEMPERATURE_KEY, temp);
    tb.sendTelemetryData(HUMIDITY_KEY, hum);
    tb.sendTelemetryData(SPL_KEY, spl);
    status = false;
  }  

}


