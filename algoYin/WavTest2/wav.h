typedef unsigned char               uint8_t;
typedef signed char                 int8_t;
typedef unsigned short int          uint16_t;
typedef signed short int            int16_t;
typedef unsigned int                uint32_t;
typedef signed int                  int32_t;

typedef struct wave_header
{
    uint8_t  riff[4]; // 'R I F F'
    uint32_t size;
    uint8_t  waveFlag[4];//' W A V E'
    uint8_t  fmt[4];//'F M T'
    uint32_t fmtLen; /* 16 for PCM */
    uint16_t tag;/* PCM = 1*/
    uint16_t channels;
    uint32_t sampFreq;
    uint32_t byteRate;
    uint16_t blockAlign;/* = NumChannels * BitsPerSample/8 */
    uint16_t bitSamp;
    uint8_t  dataFlag[4];//'D A T A'
    uint32_t length;/* data size */
} wave_header_t;

typedef struct wave_file
{
    wave_header_t header;
    uint32_t *data;
}wave_file_t;