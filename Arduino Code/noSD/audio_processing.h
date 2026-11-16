/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  Declares the audio processing functions. 
*/

#pragma once

#include <stdint.h>

// Function declarations for audio processing
float compute_mean(int16_t* buffer, int16_t num_samples);
float compute_SPL(int16_t* buffer, int16_t num_samples);
void  plot_serial(float value, int range_limit = 3000);