#include "GPS.h"
#include "LoRa.h"
#include "Pressure_Temperature.h"
#include "SDcard.h"
#include "WiFi.h"

void setup() {
  Serial.begin(115200);
}

void loop() {


  //necessary code for wifi but could make this a macro
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

  delay(1000);
}
