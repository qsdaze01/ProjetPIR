#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Yin.h"
#include "AudioDsp.h"
#include "driver/i2s.h"
#include <unistd.h>

#define PI 3.1415926535897931
#define MULT_S16 32767
#define DIV_S16 0.0000305185

#ifdef CONFIG_IDF_TARGET_ESP32
#include "driver/sdmmc_host.h"
#endif

static const char *TAG = "example";

#define MOUNT_POINT "/sdcard"

// By default, SDMMC peripheral is used.
// To enable SPI mode, uncomment the following line:

// #define USE_SPI_MODE

// ESP32-S2 and ESP32-C3 doesn't have an SD Host peripheral, always use SPI:
#if CONFIG_IDF_TARGET_ESP32S2 ||CONFIG_IDF_TARGET_ESP32C3
#ifndef USE_SPI_MODE
#define USE_SPI_MODE
#endif // USE_SPI_MODE
// on ESP32-S2, DMA channel must be the same as host id
#define SPI_DMA_CHAN    host.slot
#endif //CONFIG_IDF_TARGET_ESP32S2

// DMA channel to be used by the SPI peripheral
#ifndef SPI_DMA_CHAN
#define SPI_DMA_CHAN    1
#endif //SPI_DMA_CHAN

// When testing SD and SPI modes, keep in mind that once the card has been
// initialized in SPI mode, it can not be reinitialized in SD mode without
// toggling power to the card.

#ifdef USE_SPI_MODE
// Pin mapping when using SPI mode.
// With this mapping, SD card can be used both in SPI and 1-line SD mode.
// Note that a pull-up on CS line is required in SD mode.
#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
#define PIN_NUM_MISO 2
#define PIN_NUM_MOSI 15
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   13

#elif CONFIG_IDF_TARGET_ESP32C3
#define PIN_NUM_MISO 18
#define PIN_NUM_MOSI 9
#define PIN_NUM_CLK  8
#define PIN_NUM_CS   19

#endif //CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
#endif //USE_SPI_MODE

struct wavfile //définit la structure de l'entête d un wav
{
    char        id[4];          // doit contenir "RIFF"
    int         totallength;        // taille totale du fichier moins 8 bytes
    char        wavefmt[8];     // doit etre "WAVEfmt "
    int         format;             // 16 pour le format PCM
    short       pcm;              // 1 for PCM format
    short       channels;         // nombre de channels
    int         frequency;          // frequence d echantillonage
    int         bytes_per_second;   // nombre de bytes par secondes
    short       bytes_by_capture;
    short       bits_per_sample;  // nombre de bytes par echantillon
    char        data[4];        // doit contenir "data"
    int         bytes_in_data;      // nombre de bytes de la partie data
};

void init_buffer(float* buffer, int taille){

  for(int i = 0; i < taille; i++){
    buffer[i] = 0.0;
  }
}

void recup_echantillon(float* buffer, int pointeur){

  buffer[pointeur] = 0.0; //Méthode de Luc

}

int test_fin(){
  //Je ne sais pas encore comment faire cette méthode donc là elle sert à rien pour l'instant

  return(0);

}
void moyennage(float* donnees, float* res, int taille, int pointeur){
  float somme = 0;
  for(int i = 0; i < taille; i++){
    somme += donnees[i];
  }

  res[pointeur] = somme/((float)(taille));
}

void AudioInit(AudioDspType Adt){
  // config i2s pin numbers
  //i2s_pin_config_t pin_config;
  i2s_pin_config_t pin_config = {
    .bck_io_num = 5,
    .ws_io_num = 25,
    .data_out_num = 26,
    .data_in_num = 35
  };
  
  // config i2
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = Adt.fSampleRate,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
    .dma_buf_count = 3,
    .dma_buf_len = Adt.fBufferSize,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = false
  };
  
  // installing i2s driver
  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pin_config);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
  REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
}


// starts audio task
bool start(AudioDspType Adt)
{
  
  /* 
        *******************************************************************************************************************
        Chargement des paramètres pour la lecture de la carte SD
        *******************************************************************************************************************
  */

    esp_err_t ret;
    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t* card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
#ifndef USE_SPI_MODE
    ESP_LOGI(TAG, "Using SDMMC peripheral");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    // To use 1-line SD mode, uncomment the following line:
    slot_config.width = 1;

    // GPIOs 15, 2, 4, 12, 13 should have external 10k pull-ups.
    // Internal pull-ups are not sufficient. However, enabling internal pull-ups
    // does make a difference some boards, so we do that here.
    gpio_set_pull_mode(15, GPIO_PULLUP_ONLY);   // CMD, needed in 4- and 1- line modes
    gpio_set_pull_mode(2, GPIO_PULLUP_ONLY);    // D0, needed in 4- and 1-line modes
    gpio_set_pull_mode(4, GPIO_PULLUP_ONLY);    // D1, needed in 4-line mode only
    gpio_set_pull_mode(12, GPIO_PULLUP_ONLY);   // D2, needed in 4-line mode only
    gpio_set_pull_mode(13, GPIO_PULLUP_ONLY);   // D3, needed in 4- and 1-line modes

    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
#else
    ESP_LOGI(TAG, "Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CHAN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return(false);
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
#endif //USE_SPI_MODE

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return(false);
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

  if (!Adt.fRunning) {
    Adt.fRunning = true;
    xTaskCreatePinnedToCore(&audioTaskHandler, "Audio DSP Task", 4096, &Adt, 24, &(Adt.fHandle), 0);
    // All done, unmount partition and disable SDMMC or SPI peripheral
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Card unmounted");
#ifdef USE_SPI_MODE
    //deinitialize the bus after all devices are removed
    spi_bus_free(host.slot);
#endif

    printf("Fin \n");
    sleep(5);

    return true;
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
    Adt.fHandle = NULL;
  }
}

void audioTask(void * Adt)
{
	//Régler les problèmes de passage de variables
  // inifinite loop
  int count = 0;

  /*      Traitement des données        */

  int pointeur = 0;
  int pointeurRes = 0;
  Yin yin;
  float pitch;

  /*      Initialisation des buffers      */
  //float bufferEntree[266];
  float bufferSortie[266];
  float bufferRes[1000]; //Mettre une autre taille, c'est pas la bonne

  init_buffer(bufferEntree, 266);  
  init_buffer(bufferSortie, 266);

  while (count < 1000) {
    float samples_data_in[266]; //Adt.fBufferSize = 16; Adt.fNumInputs = 2;Adt.fNumOutputs = 2;
    float samples_data_out[266];
    
    // retrieving input buffer
    size_t bytes_read = 0;
    i2s_read((i2s_port_t)0, &samples_data_in, 2*sizeof(int16_t)*16, &bytes_read, portMAX_DELAY);
    
    // processing buffers
    for (int i = 0; i < 133; i++) {
      // input buffer to float
      float inSampleL = samples_data_in[i*2]*DIV_S16;
      float inSampleR = samples_data_in[i*2+1]*DIV_S16;
      
      // copying to output buffer
      samples_data_out[i*2] = inSampleL*MULT_S16;
      samples_data_out[i*2+1] = inSampleR*MULT_S16;
    }

    /*          Traitement          */
    Yin_init(&yin, 266, 0.08); //Je ne comprends pourquoi mais si on prend une confidence en dessous de 0.08 ça ne fonctionne plus
    pitch = Yin_getPitch(&yin, samples_data_out); // Changer le type du buffer d'entrée en float
    //buffer_length++;

    
    /*      Ajout des sorties au buffer     */
    bufferSortie[pointeur] = pitch;

    
    /*          Moyennage         */
    if(pointeur == 265){
        moyennage(bufferSortie, bufferRes, 266, pointeurRes);
        pointeurRes += 1;
    }
    
    /*      Mise à jour du buffer         */
    if(pointeur == 265){
      pointeur = 0;
    }else{
      pointeur += 1;
    }

    count++;

  }

  /*    Ecriture des résultats dans un fichier    */
  FILE *dat=fopen(MOUNT_POINT"/son.dat", "a");
  for(int i = 0; i < 1000; i++){
    fprintf(dat, "%lf \n", bufferRes[i]);
  }
  fclose(dat);

  // Task has to deleted itself beforee returning
  vTaskDelete(NULL);
}

// static cast of the audio task
void audioTaskHandler(void * Adt)
{
  audioTask(Adt);
}