/*
  Student: B00165094
  Date: 19/3/26
  Purpose: 
  defines the bluetooth code for connecting to a bluetooth speaker and playing audio.
  also includes sd card reading and checking code
*/

#include "speaker.h"
#include <Arduino.h>

File sound_file;
const char* file_path = "/dragon.wav";
BluetoothA2DPSource a2dp_source;  //defines a2dp source which sends out audio data
A2DPDefaultVolumeControl volumeControl; //defines volume control object to provide audio control

uint32_t dataSize = 0;

// function to initialize the A2DP source device
void A2DP_init(void){
  a2dp_source.set_auto_reconnect(true); //reconnect device 
  a2dp_source.set_volume(30);
  a2dp_source.start("SRS-XB13", get_sound_data);
}

// function to check if able to open .wav file
void openfile(const char* path) {
    sound_file = SD.open(path);
    if (!sound_file) {
        Serial.printf("Could not open: %s\n", path);
        return;
    }
}

// function to skip through the header so only raw data is left to read
bool skipheader(File &f) {
    // file must be larger than header size
    if(f.size() < 44) return false;

    delay(100);

    // skip to bytes 41-44 to gather data size
    f.seek(40);
    uint8_t b[4];
    f.read(b,4);
    dataSize = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);

    Serial.print("WAV data size: ");
    Serial.print(dataSize);
    Serial.println(" bytes");

    // start reading raw data
    f.seek(44);
    return true;
}

// checks if sd card is in the holder and the file exists
void check_sd(void){
    // Keep trying until successful
    while (!SD.begin(CS_PIN)) {
        Serial.println("SD card initialization failed. Retrying in 2 seconds...");
        delay(2000);  // Wait before retry
    }

    delay(500);

  if (SD.exists("dragon.wav")) {
    Serial.println("music file exists.");
  } else {
    Serial.println("music file doesn't exist.");
    return;
  }
}

// callback used by A2DP to provide the sound data
int32_t get_sound_data(Frame* frame, int32_t num_frames) {
  //check if file available
  if(!isPlaying || !sound_file || !sound_file.available()) return 0;

  int bytesToRead = num_frames * sizeof(Frame);
  int bytesRead   = sound_file.read((uint8_t*)frame, bytesToRead);

  return bytesRead / sizeof(Frame);
}
