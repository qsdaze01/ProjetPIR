//wav.c
#include <stdio.h>
#include "wav.h"

#define WAVE_FILE_HEADER_SIZE   sizeof(wave_header_t)
static char wav_header[WAVE_FILE_HEADER_SIZE];

uint32_t get_wav_data(wave_file_t *waveFile)
{
    uint8_t *dataTemp = (uint8_t *)waveFile->data;

    // check for RIFF
    memcpy(waveFile->header.riff, dataTemp, 4);
    dataTemp += 4;
    if( memcmp( (uint8_t*)waveFile->header.riff, "RIFF", 4) )
    {
        return 0;
    }

    // Get size
    memcpy(&waveFile->header.size, dataTemp, 4);
    dataTemp += 4;

    printf( "WAV header size [%d]\n", waveFile->header.size);

    // .wav file flag
    memcpy(waveFile->header.waveFlag, dataTemp, 4);
    dataTemp += 4;
    if( memcmp( (uint8_t*)waveFile->header.waveFlag, "WAVE", 4) )
    {
        return 0;
    }

    // fmt
    memcpy(waveFile->header.fmt, dataTemp, 4);
    dataTemp += 4;
    if( memcmp( (uint8_t*)waveFile->header.fmt, "fmt ", 4) )
    {
        return 0;
    }

    // fmt length
    memcpy(&waveFile->header.fmtLen, dataTemp, 4);
    dataTemp += 4;

    // Tag: PCM or not
    memcpy(&waveFile->header.tag, dataTemp, 4);
    dataTemp += 2;

    // Channels
    memcpy(&waveFile->header.channels, dataTemp, 4);
    dataTemp += 2;

    printf( "WAV channels [%d]\n", waveFile->header.channels);

    // Sample Rate in Hz
    memcpy(&waveFile->header.sampFreq, dataTemp, 4);
    dataTemp += 4;
    memcpy(&waveFile->header.byteRate, dataTemp, 4);
    dataTemp += 4;

    printf( "WAV sample_rate [%d]\n", waveFile->header.sampFreq);
    printf( "WAV byteRate [%d]\n", waveFile->header.byteRate);

    // quantize bytes for per samp point
    memcpy(&waveFile->header.blockAlign, dataTemp, 4);
    dataTemp += 2;
    memcpy(&waveFile->header.bitSamp, dataTemp, 4);
    dataTemp += 2;

    printf( "WAV bitSamp [%d]\n", waveFile->header.bitSamp);

    // Data
    memcpy(waveFile->header.dataFlag, dataTemp, 4);
    dataTemp += 4;
    if( memcmp( (uint8_t*)waveFile->header.dataFlag, "data ", 4) )
    {
        return 0;
    }
    memcpy(&waveFile->header.length, dataTemp, 4);
    dataTemp += 4;

    return 0;
}

wave_file_t wave_file_info;
uint8_t *buf;
uint32_t play_wav_file(char *file_path,char *pcm)
{
    uint32_t bytesToRead=0;
    FILE *fp=NULL;
    FILE *fptr=NULL;
    fp=fopen(file_path,"rb");
    if (!fp) {
         printf("%s can't open audio file\n",file_path);
         exit(1);
     }
     fptr=fopen(pcm,"wb");
      if (!fptr) {
         printf(" can't 2 open audio file\n");
         exit(1);
     }
     fread(&wav_header, WAVE_FILE_HEADER_SIZE, 1, fp);
     wave_file_t *newWav=&wave_file_info;
     memset(&wave_file_info, 0, sizeof(wave_file_info));
     Wav->data = (uint32_t *)&wav_header;
     get_wav_data(Wav);
     bytesToRead = (Wav->header.length - WAVE_FILE_HEADER_SIZE);

	 for (; bytesToRead > 0; bytesToRead--)
     {
         fread(&buf, 1, 1, fp);
         fwrite(&buf,1, 1, fptr);//Written as pcm to check and read char correctly
     }
     //fread(buf, 1, 1en, fp); can read wav according to the required length and type
     fclose(fp);
     fclose(fptr);
     return bytesToRead;//when play done it's 0
}

int main(void)
{
    char wave[] = "D://windlittle.wav";
    char pcm[] = "D://music2.pcm";
    uint32_t wav_len =play_wav_file(wave,pcm);
    printf("%d\n",wav_len);

    return 0;
}
