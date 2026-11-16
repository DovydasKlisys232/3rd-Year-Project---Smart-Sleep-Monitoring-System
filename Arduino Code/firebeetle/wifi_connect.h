/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 28/3/26
  Purpose: This header file holds the necessary parameters to connect to wifi and thingsboard
*/

#pragma once

#include <WiFi.h>
#include <Arduino_MQTT_Client.h>  // interact with Thingsboard over MQTT
//#include <PubSubClient.h>         // Mqtt library
#include <ThingsBoard.h>          //simplifies interaction with Thingsboard

#define WIFI_SSID     "DK_wifi"
#define WIFI_PASSWORD "ghtx4445"
#define TB_SERVER     "10.9.49.46"  // local ip address
#define TB_TOKEN      "riQvZaG5VNkGVAsbDr1E"   // token to communicate with thingsboard device
#define TB_PORT       1883U                  // default mqtt communication port

extern WiFiClient wifiClient;
extern Arduino_MQTT_Client mqttClient(wifiClient);    // initialize the mqtt client from wifi client
extern ThingsBoard tb(mqttClient);   // initialize thingsboard client

extern constexpr char TEMPERATURE_KEY[] = "temperature";
extern constexpr char HUMIDITY_KEY[] = "humidity";
extern constexpr char SPL_KEY[] = "SPL";

void initWiFi();
void check_thingsboard()
void publishTelemetry(float temp, float hum, float spl, bool status);