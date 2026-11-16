/*
  Student: B00165094
  Date: 12/3/26
  Purpose:
  This code incorporates all audio code to read in audio samples, process them and compute the intensity
  After computing the intensity, the code checks if it is above the threshold.
  If above the intensity the code will stream calming audio through a bluetooth speaker.
*/

#include "i2s_mic.h"
#include "audio_processing.h"
#include "speaker.h"
#include "UART.h"

// ==================== GLOBAL VARIABLES ====================
bool isPlaying = false;

// ==================== SETUP ====================
void setup() {
  // Serial initialization
  Serial.begin(115200);
  delay(1500);
  Serial.println(" ");

  // I2S microphone initialization
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);

  // SD card initialization (for WAV file)
  SPI.begin(CLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  check_sd();
  openfile(file_path);

  // Validate WAV file header
  if(!skipheader(sound_file)) {
    Serial.println("Invalid WAV file");
    return;
  } 

  // Bluetooth speaker initialization
  A2DP_init();

  // UART initialization (for communication with FireBeetle)
  mySerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);

  delay(500);
}

void loop() {
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK) {
        int16_t samples_read = bytesIn / 8;
        float SPL;
        
        // check if speaker connected
        if (!a2dp_source.is_connected()) {
            Serial.println("Bluetooth speaker NOT connected!");
        }

        // compute the spl after some data is read
        if (samples_read > 0) {
          SPL = compute_SPL(sBuffer, samples_read);
          mySerial.println(String(SPL)); 

          // Serial plotting debug
          static uint32_t last_plot_time = 0;
          if (millis() - last_plot_time >= 1000) {
            plot_serial(SPL, 120);
            last_plot_time = millis();
          }
        }  

        // check threshold and play audio if over threshold, else keep quiet
        if (SPL >= 50.0){
          if (!isPlaying) {
            Serial.printf("Threshold reached (%.1f dB) — starting playback\n", SPL);
            sound_file.seek(44); // rewind to audio data
            isPlaying = true;
          } 
        }
        else{
          isPlaying = false;
        }
    }
    
  delay(1000);
}