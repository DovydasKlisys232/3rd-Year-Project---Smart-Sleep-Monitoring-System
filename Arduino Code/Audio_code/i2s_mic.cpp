/*
  Student: B00165094
  Date: 12/3/26
  Purpose: 
  Implements the functions defined in i2s_mic.h
  Used for i2s hardware configuration and pin setup
*/

#include "i2s_mic.h"
#include <Arduino.h>

// Define the buffer here (one definition across the project)
int16_t sBuffer[bufferLen];

// sets up the i2s configuration
// configure hardware (DMA setup, bit rate)
void i2s_install(void) {
    const i2s_config_t i2s_config = {
        .mode               = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate        = 44100,
        .bits_per_sample    = i2s_bits_per_sample_t(16),
        .channel_format     = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
        .intr_alloc_flags   = 0,
        .dma_buf_count      = 8,
        .dma_buf_len        = bufferLen,
        .use_apll           = false
    };

    // pass in the i2s port, driver configuration, event queue size and queue handle
    if (i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL) != ESP_OK) {
        Serial.println("ERROR: Failed to install I2S driver");
        return;
    }
}

// set up i2s pins
// define all necessary pins
void i2s_setpin(void) {
    const i2s_pin_config_t pin_config = {
        .bck_io_num    = I2S_SCK,
        .ws_io_num     = I2S_WS,
        .data_out_num  = I2S_PIN_NO_CHANGE,
        .data_in_num   = I2S_SD
    };

    // pass i2s port and pin configurations
    if (i2s_set_pin(I2S_PORT, &pin_config) != ESP_OK) {
        Serial.println("ERROR: Failed to set I2S pins");
        i2s_driver_uninstall(I2S_PORT);
        return;
    }
}