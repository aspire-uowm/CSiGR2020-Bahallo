#include "defines.h"

//Basic Libraries
#include <Wire.h>
#include <SD.h>

SPIClass sd_spi(HSPI);

char GPSBuffer[150];
byte GPSIndex=0;
double gps_latitude = 0.0;
double gps_longitude = 0.0;
char lat_direction, lgt_direction;

uint8_t buf[]="Panda";
uint8_t len=5;

void setup() {
  Serial.begin(115200);
}

void loop() {


  necessary for wifi
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}
