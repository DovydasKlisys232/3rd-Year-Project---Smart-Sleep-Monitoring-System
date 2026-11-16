/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  Declares the audio processing functions. 
*/

#pragma once

#include <stdint.h>

// Function that computes the mean value of audio samples to determine the DC bias
float compute_mean(int16_t* buffer, int16_t num_samples);
// Function that computes the SPL after a number of saved audio samples 
float compute_SPL(int16_t* buffer, int16_t num_samples);
// Function to plot the SPL values on a graph in serial plotter
void  plot_serial(float value, int range_limit = 3000);