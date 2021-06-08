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

#include "audioData.h"

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

void init_buffer(float* buffer, int taille){

  for(int i = 0; i < taille; i++){
    buffer[i] = 0.0;
  }
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
bool start(AudioDspType Adt){
  
  /* *******************************************************************************************************************
    Chargement des paramètres pour la lecture de la carte SD
     *******************************************************************************************************************/

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
    xTaskCreatePinnedToCore(&audioTask, "Audio DSP Task", 100000, &Adt, 2, &(Adt.fHandle), 0);
    vTaskSuspend(NULL);
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

  /*      Déclaration des variables       */

  int pointeur = 0;
  int count = 0;
  Yin yin;
  float pitch = 0.0;

  /*      Initialisation des buffers      */
  
  //float bufferSortie[266];
  float bufferRes[1000]; //Mettre une autre taille, c'est pas la bonne
  int16_t samples_data_in[1500];
  float bufferEntree[1500];
  //float temp[2660];

  //init_buffer(bufferSortie, 1000);
  int buffer_length = 100;
  int array_length = sizeof(audio)/sizeof(int16_t);
  float audio_float[array_length];
  for (int i = 0; i<array_length;i++){
    audio_float[i]=(float) audio[i];
  }

  while (pitch<10){
    Yin_init(&yin, buffer_length, 0.01);
    pitch = Yin_getPitch(&yin,audio_float);
    buffer_length++;
  }
  printf("%f\n",pitch );

  /*    Boucle de traitement des données  */


  while (count < 100) {
    size_t bytes_read = 0;
    i2s_read((i2s_port_t)0, &samples_data_in, 1500*sizeof(int16_t), &bytes_read, portMAX_DELAY);

    for(int i = 0; i < 1500; i++){
      bufferEntree[i] = (float) (samples_data_in[i]);
      //printf("%f\n",bufferEntree[i]);
    }

    pitch = 0;
    buffer_length = 100;

    while (pitch<10 && buffer_length<250){
      //printf("counterPitch : %d\n", buffer_length );
      Yin_init(&yin, buffer_length, 0.01);
      pitch = Yin_getPitch(&yin,bufferEntree);
      buffer_length++;
      free(yin.yinBuffer);
    }
    printf("Fondamentale : %f\n", pitch );
    printf("Tour numéro %d\n", count );
    count++;
    
  }

    /*          Traitement          */
/*
    Yin_init(&yin, 266, 0.1); //Je ne comprends pourquoi mais si on prend une confidence en dessous de 0.08 ça ne fonctionne plus
    pitch = Yin_getPitch(&yin, bufferEntree); 
    free(yin.yinBuffer);  
    
    bufferRes[count] = pitch;
*/
    /*      Ajout des sorties au buffer     */
    /*for(int i = 0; i < 266; i++){
      bufferSortie[i] = pitch;
      //temp[i + 266*count] = pitch;
    }*/
        
    /*          Moyennage         */
/*
    //moyennage(bufferSortie, bufferRes, 266, count);
    count++;
    
    //printf("%d\n", count);
  }
*/  
  /*    Ecriture des résultats dans un fichier    */

  FILE *dat=fopen(MOUNT_POINT"/son.dat", "w");
  for(int i = 0; i < 1000; i++){
    fprintf(dat, "%d \n", (int)bufferEntree[i]);
    //fprintf(dat, "%lf \n", bufferRes[i]);
  }

  fclose(dat);
  printf("a\n");

  // Task has to deleted itself beforee returning
  vTaskDelete(NULL);
}