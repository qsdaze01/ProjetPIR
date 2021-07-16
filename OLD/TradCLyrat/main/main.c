#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "ES8388.h"
#include "AudioDsp.h"

void app_main(){
	initES();

	AudioDspType Adt;

	Adt.fSampleRate = 48000;
	Adt.fBufferSize = 16;
	Adt.fNumInputs = 2;
	Adt.fNumOutputs = 2;
	Adt.fHandle = NULL;
	Adt.fRunning = false;

	//audioDsp(48000,16);
  	AudioInit(Adt);
  	start(Adt);

	// waiting forever
  	vTaskSuspend(NULL);

	return;
}
