/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  Declares the bluetooth audio code functions.
*/

#pragma once

#include "BluetoothA2DPSource.h"
#include <math.h>

#define SPL_MIN   60.0
#define SPL_MAX  100.0

#define c3_frequency  130.81

extern bool isPlaying;

extern BluetoothA2DPSource a2dp_source;  //defines a2dp source which sends out audio data 
extern A2DPDefaultVolumeControl volumeControl; //defines volume control object to provide audio control

// function declerations for bluetooth speaker and sd functions
int32_t get_sound_data(Frame* frame, int32_t num_frames);
uint8_t splToVolume(float spl);
void check_SPL(bool isPlaying, float SPL);