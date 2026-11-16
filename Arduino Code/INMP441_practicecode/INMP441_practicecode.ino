// Include I2S driver
#include <driver/i2s.h>
#include "BluetoothA2DPSource.h"
#include <math.h>
 
BluetoothA2DPSource a2dp_source;

// audio format: 16-bit signed PCM, stereo, 44.1 kHz
const int SAMPLE_RATE = 44100;
const float frequency = 440.0;

// Connections to INMP441 I2S microphone
#define I2S_WS 25
#define I2S_SD 33
#define I2S_SCK 32

//configure the driver
 
// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0
 
// Define input buffer length
#define bufferLen 64
int16_t sBuffer[bufferLen];


// sets how the I2S behaves. Installing the I2S driver
// pass in a port number, i2S structure, event queue size and handle
void i2s_install() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),  //master mode: esp32 generates clock, RX(receiving audio)
    .sample_rate = 44100,                               //sample rate 
    .bits_per_sample = i2s_bits_per_sample_t(16),       //16 bit sample rate
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,        // only left channel (INMP441 is mono)
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };
 
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}
 
void i2s_setpin() {
  // Set I2S pin configuration
  // defining gpio pin numbers
  // if signal is unused pass the macro I2S_PIN_NO_CHANGE
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,   // not transmitting, collecting audio
    .data_in_num = I2S_SD 
  };
 
  i2s_set_pin(I2S_PORT, &pin_config);
}

uint16_t get_sound_data(uint8_t *data, uint32_t byteCount) {
  


}
 
void setup() {
 
  // Set up Serial Monitor
  Serial.begin(115200);
  Serial.println(" ");
 
  delay(1000);
 
  // Set up I2S
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);

  // Set up bluetooth device
  a2dp_source.set_data_callback(get_sound_data);
  a2dp_source.start("SRS-XB13");
 
  delay(500);
}
 
void loop() {
 
  // False print statements to "lock range" on serial plotter display
  // Change rangelimit value to adjust "sensitivity"
  int rangelimit = 3000;
  Serial.print(rangelimit * -1);
  Serial.print(" ");
  Serial.print(rangelimit);
  Serial.print(" ");
 
  // Get I2S data and place in data buffer
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
 
  if (result == ESP_OK)
  {
    // Read I2S data buffer
    int16_t samples_read = bytesIn / 8;
    if (samples_read > 0) {
      float mean = 0;
      for (int16_t i = 0; i < samples_read; ++i) {
        mean += (sBuffer[i]);
      }
 
      // Average the data reading
      mean /= samples_read;
 
      // Print to serial plotter
      Serial.println(mean);
    }
  }
}

// to perform prepare the data for sending, call i2s_write() and pass data buffer address and data length
// to retrieve received data use i2s_read(). retrieves from I2S DMA Rx buffer.
// temporary stop I2S driver with i2s_stop(), disabling I2S Tx/Rx units until the function i2s_start().
