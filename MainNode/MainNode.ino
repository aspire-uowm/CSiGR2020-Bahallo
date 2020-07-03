#include "GPS.h"
#include "LoRa.h"
#include "Pressure_Temperature.h"
#include "SDcard.h"
#include "WiFi.h"
#include "ttnModule.h"
#include "UdpWifi.h"

void setup() {
  Serial.begin(115200);

  //GPSinit();//gps initialiization
  //LoRa_Init();//LoRa initialization
  //Pressure_TemperatureInit();//BMP280 initialization
  //SDcard_Init();//initalize SD card pins
  //wifi_sniffer_init();// start asynch wifi listening

  //ttnDeviceInit();

  UdpInit();
}

void loop() {

  //ttnDevice_get();

  //necessary code for wifi but could make this a macro
  //vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  //esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

  GetUdpackets();

  delay(1000);
}
