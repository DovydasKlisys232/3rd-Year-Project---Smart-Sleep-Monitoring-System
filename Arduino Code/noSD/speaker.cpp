/*
  Student: B00165094
  Date: 19/3/26
  Purpose: 
  defines the bluetooth code for connecting to a bluetooth speaker and playing audio.
  also includes sd card reading and checking code
*/

#include "speaker.h"
#include <Arduino.h>

bool isPlaying = false;

const float pi_2 = PI * 2.0;
const float angular_frequency = pi_2 * c3_frequency;

// angular_frequency (radians per second) / sampling rate (samples per second)
// gives radians changed per sample period.
const float deltaAngle = angular_frequency / 44100.0;

BluetoothA2DPSource a2dp_source;  //defines a2dp source which sends out audio data
A2DPDefaultVolumeControl volumeControl; //defines volume control object to provide audio control

// sets the volume of the speaker
uint8_t splToVolume(float spl) {
  float clamped = constrain(spl, SPL_MIN, SPL_MAX);
  return (uint8_t)map((long)clamped, (long)SPL_MIN, (long)SPL_MAX, 0, 127);
}

// callback used by A2DP to provide the sound data
int32_t get_sound_data(Frame* frame, int32_t frame_count) {
  static float angle = 0.0f;
    const float amplitude = 0.3f * INT16_MAX;

    for (int i = 0; i < frame_count; i++) {
        if (!isPlaying) {
          // output silence
          frame[i].channel1 = 0;
          frame[i].channel2 = 0;
          continue;
        }

        float sample = amplitude * sinf(angle);

        frame[i].channel1 = sample;
        frame[i].channel2 = sample;

        angle += deltaAngle;
        if (angle >= TWO_PI) angle -= TWO_PI;
    }

    return frame_count;
}

// check spl value
void check_SPL(bool isPlaying, float SPL){
  if (SPL >= 40.0){
    if (!isPlaying) {
      Serial.printf("Threshold reached (%.1f dB) — starting playback\n", SPL);
      isPlaying = true;
    } 
  }
  else{
    isPlaying = false;
  }
}
