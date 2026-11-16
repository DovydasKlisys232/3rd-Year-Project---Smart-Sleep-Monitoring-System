#include "BluetoothA2DPSource.h"
#include <math.h>

BluetoothA2DPSource a2dp_source;

// Audio format: 16‑bit signed PCM, stereo, 44.1 kHz
const int SAMPLE_RATE = 44100;
const float frequency = 440.0;   // A4 tone
float phase = 0.0;
float phaseIncrement = 2.0 * M_PI * frequency / SAMPLE_RATE;

// callback 
int32_t get_sound_data(uint8_t *data, int32_t byteCount) {
    int16_t *samples = (int16_t *)data;
    int sampleCount = byteCount / 2;  // 2 bytes per sample

    for (int i = 0; i < sampleCount; i += 2) {
        // Generate a sine wave sample
        int16_t sample = (int16_t)(sin(phase) * 30000);

        // Stereo: left and right channels
        samples[i] = sample;       // Left
        samples[i + 1] = sample;   // Right

        phase += phaseIncrement;
        if (phase > 2.0 * M_PI) phase -= 2.0 * M_PI;
    }

    return byteCount;
}

void setup() {
  a2dp_source.set_data_callback(get_sound_data);
  a2dp_source.start("SRS-XB13");  
}

void loop() {}


//provide your own real PCM audio samples inside callback
// ensure the samples are 16-bit signed, 44.1 kHz or 48 kHz, stereo (A2DP requirement)
// fill the data buffer with your audio
// return the number of bytes you actually wrote
//Bluetooth Receiver → Audio Decoder → DAC → Amplifier → Speaker Driver