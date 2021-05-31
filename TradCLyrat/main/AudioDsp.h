#ifndef __AUDIODSP_H
#define __AUDIODSP_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*class AudioDsp
{
public:
  AudioDsp(int SR, int BS);
  bool start();
  void stop();
private:
  void audioTask();
  static void audioTaskHandler(void* arg);
  
  int fSampleRate, fBufferSize, fNumInputs, fNumOutputs;
  TaskHandle_t fHandle;
  bool fRunning;
  
  Echo echoL, echoR;
};*/

typedef struct {
	
	int fSampleRate, fBufferSize, fNumInputs, fNumOutputs;
	TaskHandle_t fHandle;
	bool fRunning;
  
	//Echo echoL, echoR;

} AudioDspType;

void AudioInit(AudioDspType Adt);
bool start(AudioDspType Adt);
void stop(AudioDspType Adt);
void audioTask(AudioDspType Adt);
void audioTaskHandler(AudioDspType Adt);

#endif