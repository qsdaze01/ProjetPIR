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
	Adt.fBufferSize = 266;
	Adt.fNumInputs = 1;
	Adt.fNumOutputs = 1;
	Adt.fHandle = NULL;
	Adt.fRunning = false;

  	AudioInit(Adt);
  	start(Adt);

  	// waiting forever
    vTaskSuspend(NULL);

	//return;
}
