//#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "esp_flash.h"
//include "esp_flash_spi_init.h"
//#include "esp32/ulp.h"
//#include "driver/touch_pad.h"
//#include "driver/rtc_io.h"
//#include "soc/rtc.h"
#include "esp_spi_flash.h"
#include "rom/spi_flash.h"

static RTC_DATA_ATTR struct timeval sleep_enter_time;

//static uint32_t g_wbuf[SPI_FLASH_SEC_SIZE / 4];
uint8_t g_rbuf[SPI_FLASH_SEC_SIZE / 2];

uint8_t * iteracion = 0x50001fff;
uint8_t * key_addr = 0x50001fff - 512;
//uint8_t * key_addr = (0x3FFAE000 + 102400 - 4096);
uint8_t * PUF_pSRAM = 0x3F800000+4096;
uint8_t * HD_pSRAM = 0x3F800000+4096+4096;
uint8_t * mask_pSRAM = 0x3F800000+4096+4096+4096;
uint8_t * addr_SRAM = (0x3FFAE000 + 102400 + 51200 + 25600);
//uint8_t * addr_flash = 0x3F700000;
//esp_flash_t * addr_flash = 0x3F700000;
uint8_t bandera = 0;



void app_main()
{
    printf("%d,%d\n",*(iteracion),bandera);
    if (*(iteracion) >= 80){
        bandera = 1;
    }

    struct timeval now;
    gettimeofday(&now, NULL);
    int sleep_time_ms = (now.tv_sec - sleep_enter_time.tv_sec) * 1000 + (now.tv_usec - sleep_enter_time.tv_usec) / 1000;

    switch (esp_sleep_get_wakeup_cause()) {

        case ESP_SLEEP_WAKEUP_TIMER: {
            printf("Wake up from timer. Time spent in deep sleep: %dms\n", sleep_time_ms);
            break;
        }
        case ESP_SLEEP_WAKEUP_UNDEFINED:
        default:
            printf("Wake up from board reset\n");
            *(iteracion) = 0;
            bandera = 0;
    }
 
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    const int wakeup_time_sec = 30;
    esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);

    //uint8_t * addr_mem_SRAM2 = (0x3FFAE000 + 102400);
    //int i = 0;
	printf("Start\n");
	
    uint32_t f_PUF_addr = 0x200000;
    uint32_t fmask_addr = 0x205000;
    uint32_t fmask_w_addr = 0x205000;

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    //Paso 1 -> Leer SRAM a DRAM
    for(int i = 0 ; i < 2048 ; i++){
        //*(PUF_pSRAM + i) = *(addr_SRAM + i);
        //PUF_pSRAM[i]=addr_SRAM[i];
        printf("%d\n",addr_SRAM[i]);
        //printf("%d\n",PUF_pSRAM[i]);
    }

    //Paso2/3 similares Lee y comprueba "iteracion"
    if(*(iteracion) == 0){
        spi_flash_erase_sector(f_PUF_addr / SPI_FLASH_SEC_SIZE);
        spi_flash_write(f_PUF_addr, addr_SRAM, 2048);
        //while(1);

    }else if(*iteracion <20){
        //Paso 8 -> Lee datos de Flash "f_PUF"
        memset(g_rbuf, 0, sizeof(g_rbuf));
        spi_flash_read(f_PUF_addr, g_rbuf, sizeof(g_rbuf));
        for(int i = 0 ; i < 2048 ; i++){
            *(addr_SRAM + i) = g_rbuf[i]^PUF_pSRAM[i];
            printf("%d\n", g_rbuf[i]);
        }
        while(1);
        //repetir 8 9 y 10
        f_PUF_addr += SPI_FLASH_SEC_SIZE;
        memset(g_rbuf, 0, sizeof(g_rbuf));
        //printf("reading at %x\n", f_PUF_addr);
        spi_flash_read(f_PUF_addr, g_rbuf, sizeof(g_rbuf));
        for(int i = 0 ; i < 1024 ; i++){
            *(mask_pSRAM + 1024 + i) = g_rbuf[i]^PUF_pSRAM[i+1024];
           // printf("%d\n", g_wbuf[i]);
        }
        if (*(iteracion)>1){
            //Paso 11 -> Lee datos de la Flashs "mascara"
            memset(g_rbuf, 0, sizeof(g_rbuf));
            //printf("reading at %x\n", fmask_addr);
            spi_flash_read(fmask_addr, g_rbuf, sizeof(g_rbuf));
            //Paso 12-> OR con XOR(PUF y f_PUF) y anterior mascara
            for(int i = 0 ; i < 1024 ; i++){
                *(mask_pSRAM + i) = g_rbuf[i]|mask_pSRAM[i];
            }
            fmask_addr += SPI_FLASH_SEC_SIZE;
            //Paso 11 -> Lee datos de la Flashs "mascara"
            memset(g_rbuf, 0, sizeof(g_rbuf));
            //printf("reading at %x\n", fmask_addr);
            spi_flash_read(fmask_addr, g_rbuf, sizeof(g_rbuf));
            //Paso 12-> OR con XOR(PUF y f_PUF) y anterior mascara
            for(int i = 0 ; i < 1024 ; i++){
                *(mask_pSRAM + 1024 + i) = g_rbuf[i]|mask_pSRAM[i+1024];
            }
        }

        //Paso 13 -> Crea buffer de 1024 bytes
        for (int j = 0; j < 1024; ++j) {
            //g_wbuf[j] = mask_pSRAM [j];
        }
        
        spi_flash_erase_sector(fmask_w_addr / SPI_FLASH_SEC_SIZE);
       // spi_flash_write(fmask_addr, g_wbuf, sizeof(g_wbuf));

        
        fmask_w_addr += SPI_FLASH_SEC_SIZE;

        
        for (int j = 0; j < 1024; ++j) {
           // g_wbuf[j] = mask_pSRAM [1024 + j];
        }

        //Paso 5 -> Almacena buffer en Flash "f_PUF"
        spi_flash_erase_sector(fmask_w_addr / SPI_FLASH_SEC_SIZE);
       // spi_flash_write(fmask_w_addr , g_wbuf, sizeof(g_wbuf));
    }else{
        memset(g_rbuf, 0, sizeof(g_rbuf));
            //printf("reading at %x\n", fmask_addr);
            spi_flash_read(fmask_addr, g_rbuf, sizeof(g_rbuf));
            
            for(int i = 0 ; i < 1024 ; i++){
                printf("%d\n",g_rbuf[i]);
            }
            fmask_addr += SPI_FLASH_SEC_SIZE;
            //Paso 11 -> Lee datos de la Flashs "mascara"
            memset(g_rbuf, 0, sizeof(g_rbuf));
            //printf("reading at %x\n", fmask_addr);
            spi_flash_read(fmask_addr, g_rbuf, sizeof(g_rbuf));
            //Paso 12-> XOR con XOR(PUF y f_PUF) y anterior mascara
            for(int i = 0 ; i < 1024 ; i++){
                printf("%d\n",g_rbuf[i]);
                /*printf("%d,",g_rbuf[i]);
                if (i%32 == 0){
                    printf("\n");
                }else{
                    printf(",");
                }*/
            }
            while(1);
    }
    


    //Paso 14 -> Actualiza direccion
    *(iteracion) = *(iteracion) + 1;

    //Paso 15 -> Duerme. 
    if(!bandera){
        gettimeofday(&sleep_enter_time, NULL);
        printf("A la cama\n");
        esp_deep_sleep_start();
    }else{
        *(iteracion) = 0;
        printf("-------------------otra-------------------");
        while(1);
    }
}
