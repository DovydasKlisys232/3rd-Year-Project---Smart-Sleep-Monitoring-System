/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  This code includes all i2s protocol setup functions and defining the i2s pins 
*/

#pragma once

#include <driver/i2s.h>
#include <stdint.h>

// Audio format constants
const int32_t SAMPLE_RATE     = 44100;
const int32_t RECORD_SECONDS  = 5;
const int16_t BITS_PER_SAMPLE = 16;
const uint16_t NUM_CHANNELS   = 1;

// INMP441 I2S pin connections to ESP32 classic
#define I2S_WS   25
#define I2S_SD   33
#define I2S_SCK  32

// I2S peripheral to use
#define I2S_PORT I2S_NUM_0

// DMA buffer length (number of samples per read)
#define bufferLen 64

// Shared sample buffer. Stores collected audio samples in raw format
extern int16_t sBuffer[bufferLen];

// Function that sets up the i2s configuration
void i2s_install(void);
// Function that sets up that i2s pins
void i2s_setpin(void);