/*
  Student: Dovydas Klisys
  ID: B00165094
  Date: 27/3/26
  Purpose: this is the main program for the esp32-c6. It is incharge of collecting temperature and humidity data, collecting the SPL volume data
  from the esp32 classic through UART communication and displaying this data on the tft screen. it also turns on a fan when the temperature
  threshold is met. Its final job is to send the data out to the thread border router.
*/

#include "wifi_connect.h"
#include "Temp-Hum.h"
#include "screen.h"
#include "UART.h"

#define FAN_PIN 3

// variables to store readings
float temperature;
float humidity;
float SPL;
bool status;

HardwareSerial mySerial(1);

void setup() {
  Serial.begin(115200);
  delay(500);

  mySerial.begin(BAUD, SERIAL_8N1, RXD, TXD);  // UART setup
  
  pinMode(FAN_PIN, OUTPUT);
  Wire.begin(SDA_PIN, SCL_PIN);  //  select your pin numbers here

  tft.init(240, 320); //sets up screen to correct resolution for 2 inch screen
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);
  display();  // produce initial display screen

  delay(2000);

  Serial.println("Booted!");
}

void loop() {
  // check sensor status
  // must perform read() before you can collect any readings
  int status = DHT.read();
  check_stats(status);

  // collect temperature and humidity data
  temperature = DHT.getTemperature();
  humidity = DHT.getHumidity();

  // Check if data is available to read and hasn't reached new line
  while(mySerial.available()) {
    // read data into string
    String received = mySerial.readStringUntil('\n');
    received.trim(); // strips the \r that println() also sends
    SPL = received.toFloat();
    Serial.println("Received: " + received);
  }

  // update the readings on the screen
  update(temperature, humidity, SPL, status);

  // send data to thingsboard
  publishTelemetry(temperature, humidity, SPL, status);

  if(temperature > 25){
    digitalWrite(FAN_PIN, HIGH);
  }
  else{
    digitalWrite(FAN_PIN, LOW);
  }

}