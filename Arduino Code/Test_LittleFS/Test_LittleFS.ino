/*
  Practice code to test LittleFS library
  LittleFS is a memory software for ESP32
  I will open a file using LittleFS, save it to esp32 memory and write to it.
  I will then read from this file.
*/

#include <Arduino.h>
#include "FS.h"
#include "LittleFS.h"

//---------------------------------------------------------------------------------------------//
//functions
//---------------------------------------------------------------------------------------------//

// write to file function
// pass fs object, file path and the message to function
// this function will just print out one message to a file
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

// read from existing file function
void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading from file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println(" can't open file to read");
    return;
  }
  
  Serial.println("reading");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  Serial.println(" ");
  delay(1000);

  // Mount LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("LittleFS mount failed!");
    while (true) delay(1000);
  }
  Serial.println("LittleFS mounted.");

  // print out information
  Serial.printf("Total LittleFS: %u bytes, Used: %u bytes\n", LittleFS.totalBytes(), LittleFS.usedBytes());

  writeFile(LittleFS, "/hello.txt", "hello ");
  readFile(LittleFS, "/hello.txt");
  deleteFile(LITTLEFS, "/hello.txt");
 
  delay(500);

}

void loop() {

}
