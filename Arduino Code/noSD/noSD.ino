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

HardwareSerial mySerial(2);

void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println(" ");

  // start i2s interface
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);

  // start bluetooth speaker, allow it to reconnect, set volume and state correct source
  a2dp_source.set_auto_reconnect(true); //reconnect device 
  a2dp_source.set_volume(80);
  a2dp_source.start("SRS-XB13", get_sound_data); 

  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  mySerial.begin(BAUD, SERIAL_8N1, RXD2, TXD2);

  delay(500);
}

void loop() {
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK) {
        int16_t samples_read = bytesIn / 8;
        float SPL = 0.0;
        // check if speaker connected
        if (!a2dp_source.is_connected()) {
            Serial.println("Bluetooth speaker NOT connected!");
        }
        // compute the spl after some data is read
        if (samples_read > 0) {
          SPL = compute_SPL(sBuffer, samples_read);
          mySerial.println(String(SPL)); 
          // Use a timer or millis() instead of delay(1000)
          static uint32_t last_plot_time = 0;
          if (millis() - last_plot_time >= 1000) {
            plot_serial(SPL, 120);
            last_plot_time = millis();

            // check threshold and play audio if over threshold, else keep quiet
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
        }     
    }
}
