/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  Declares the bluetooth audio code functions.
*/

#pragma once

#include "BluetoothA2DPSource.h"
#include <SD.h>
#include <SPI.h>

// sd card module pin definitions
#define CS_PIN 15
#define CLK_PIN  14
#define MOSI_PIN 13
#define MISO_PIN 12

extern File sound_file; // stores name of audio file containing calm music
extern const char* file_path;
extern BluetoothA2DPSource a2dp_source;  //defines a2dp source which sends out audio data 
extern A2DPDefaultVolumeControl volumeControl; //defines volume control object to provide audio control

extern bool isPlaying;  // boolean variable to track bluetooth speaker condition (is it playing music or not)

// function to initialize the A2DP source device
void A2DP_init(void);
// function to check if able to open .wav file
void openfile(const char* path);
// function to skip the header of the .wav music file
bool skipheader(File &f);
// function to check if sd card module contains an sd card
void check_sd(void);
// function to gather the audio data from .wav file to play back to speaker
int32_t get_sound_data(Frame* frame, int32_t num_frames);