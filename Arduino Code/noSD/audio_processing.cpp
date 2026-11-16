/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  defines the audio processing funcitons
  the function definitions tells you what the esp32 will do with the audio samples. 
*/

#include "audio_processing.h"
#include <Arduino.h>

// find average value of all samples to gather dc bias
float compute_mean(int16_t* buffer, int16_t num_samples) {
  float mean = 0.0f;
  for (int16_t i = 0; i < num_samples; i++) {
      mean += buffer[i];
  }
  return mean / num_samples;
}

float compute_SPL(int16_t* buffer, int16_t num_samples) {
  //remove DC offset by subtracting the mean from each sample so the signal oscillates arouns zero
  float mean = compute_mean(buffer, num_samples);

  // calculate the RMS value of a number of samples after removing dc offset
  float sum_of_squares = 0.0f;
  for (int16_t i = 0; i < num_samples; i++) {
      float sample = (float)buffer[i] - mean;
      sum_of_squares += sample * sample;
  }
  float RMS = sqrt(sum_of_squares/num_samples);

  // calculating dbfs
  float dbfs = 20.0f * log10f(RMS/32768.0f);

  //return db SPL
  return 94.0f + (dbfs + 26.0f);
}

void plot_serial(float value, int range_limit) {
    // Anchor lines so the Serial Plotter y-axis stays fixed
    Serial.print(0);
    Serial.print(" ");
    Serial.print(range_limit);
    Serial.print(" ");
    Serial.println(value);
}