#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define SD_CS 13
#define SD_SCK 14
#define SD_MOSI 15
#define SD_MISO 2

#define LOG_PATH "/mes.log"

/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      14
 *    VSS      GND
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */

static SPIClass sd_spi(HSPI);

//static uint8_t buf[]="Panda";
//static uint8_t len=5;

//initialize te on board sdcard pins
String SDcard_Init(){
  sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  //man I really wanted a oneliner
  return (!SD.begin(SD_CS, sd_spi)) ? "SD Card: mounting failed." : "SD Card: mounted." ;
}

//Write to sdcard file
void SDcard_Run(uint8_t* buf,uint8_t len){
  File test = SD.open(LOG_PATH, FILE_APPEND);
  
  if (!test)Serial.println("SD Card: writing file failed."); 
  else {
      Serial.printf("SD Card: appending data to %s.\n", LOG_PATH);
      test.write(buf,len);
      test.printf("\n");
      test.close();
   }    
}
