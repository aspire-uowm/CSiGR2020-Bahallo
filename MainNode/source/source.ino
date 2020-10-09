#include "GPS.h"
#include "LoRa.h"
#include "Pressure_Temperature.h"
#include "SDcard.h"
#include "WiFi.h"
#include "WiFiServer.h"

void setup() {
  Serial.begin(115200);

  //GPSinit();//gps initialiization
  LoRa_Init();//LoRa initialization
  //Pressure_TemperatureInit();//BMP280 initialization
  //SDcard_Init();//initalize SD card pins
  //wifi_sniffer_init();// start asynch wifi listening

    Serial.println(WiFi.macAddress());
  //InitServer();
}

void loop() {
  String Data = "From Node: ";

  //necessary code for wifi but could make this a macro
  /*vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);*/

  //Data += Listen();
  
  //PressureTemperaturePrint();/* display */
  //for(int i=0; i<3; i++)Data += String(getPrTemAlt()[i]);
  
  //GPSrun();
  //for(int i=0; i<2; i++)Data += String(GPSrun()[i]);
  
  //SDcard_Run((uint8_t*)atoi(Data.c_str()),(uint8_t)Data.length());
  
  LoRa_Run(Data);
  delay(500);
}
