#include <stdio.h>
#include <cmath>
#include <algorithm>

#include "AudioDsp.h"
#include "driver/i2s.h"

#define PI 3.1415926535897931
#define MULT_S16 32767
#define DIV_S16 0.0000305185





// starts audio task
bool start(AudioDspType Adt)
{
  if (!Adt.fRunning) {
    Adt.fRunning = true;
    return (xTaskCreatePinnedToCore(Adt.audioTaskHandler, "Audio DSP Task", 4096, Adt, 24, &(Adt.fHandle), 0) == pdPASS);
  } 
  else {
    return true;
  }
}

// stops audio task
void stop(AudioDspType Adt)
{
  if (Adt.fRunning) {
    Adt.fRunning = false;
    vTaskDelay(1/portTICK_PERIOD_MS);
    Adt.fHandle = nullptr;
  }
}

void audioTask(AudioDspType Adt)
{
  // inifinite loop
  while (Adt.fRunning) {
    int16_t samples_data_in[Adt.fNumOutputs*Adt.fBufferSize];
    int16_t samples_data_out[Adt.fNumOutputs*Adt.fBufferSize];
    
    // retrieving input buffer
    size_t bytes_read = 0;
    i2s_read((i2s_port_t)0, &samples_data_in, Adt.fNumInputs*sizeof(int16_t)*Adt.fBufferSize, &bytes_read, portMAX_DELAY);
    
    // processing buffers
    for (int i = 0; i < Adt.fBufferSize; i++) {
      // input buffer to float
      float inSampleL = samples_data_in[i*Adt.fNumInputs]*DIV_S16;
      float inSampleR = samples_data_in[i*Adt.fNumInputs+1]*DIV_S16;
      
      // DSP
      //inSampleL = echoL.tick(inSampleL);
      //inSampleR = echoR.tick(inSampleR);
      
      // copying to output buffer
      samples_data_out[i*Adt.fNumOutputs] = inSampleL*MULT_S16;
      samples_data_out[i*Adt.fNumOutputs+1] = inSampleR*MULT_S16;
    }
    // transmitting output buffer
    size_t bytes_written = 0;
    i2s_write((i2s_port_t)0, &samples_data_out, Adt.fNumOutputs*sizeof(int16_t)*Adt.fBufferSize, &bytes_written, portMAX_DELAY);
  }
  // Task has to deleted itself beforee returning
  vTaskDelete(nullptr);
}

// static cast of the audio task
void audioTaskHandler(void* arg)
{
  AudioDsp* audio = static_cast<AudioDsp*>(arg);
  audio->audioTask();
}