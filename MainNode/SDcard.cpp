#include "SDcard.h"

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

void SDcard_Init(){
  
  sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    
  if (!SD.begin(SD_CS, sd_spi))Serial.println("SD Card: mounting failed.");
  else Serial.println("SD Card: mounted.");
}

void SDcard_Run() {
  File test = SD.open(LOG_PATH, FILE_APPEND);
  
  if (!test)Serial.println("SD Card: writing file failed."); 
  else {
      Serial.printf("SD Card: appending data to %s.\n", LOG_PATH);
      test.write(buf,len);
      test.printf("\n\n");
      test.close();
   }  
}