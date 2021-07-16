#ifndef __AUDIODSP_H
#define __AUDIODSP_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef struct {
	
	int fSampleRate, fBufferSize, fNumInputs, fNumOutputs;
	TaskHandle_t fHandle;
	bool fRunning;

} AudioDspType;

void AudioInit(AudioDspType Adt);
bool start(AudioDspType Adt);
void stop(AudioDspType Adt);
void audioTask(void * Adt);
void audioTaskHandler(void * Adt);

#endif