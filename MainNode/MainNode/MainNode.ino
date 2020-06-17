//Basic Libraries
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//BMP280 Includes
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Libraries for LoRa
#include <LoRa.h>

#define use_UDP
#ifdef use_UDP
  #include <WiFi.h>
  #include <WiFiUdp.h>
#else
  #include "esp_wifi.h"
  #include "esp_wifi_types.h"
  #include "esp_system.h"
  #include "esp_event_loop.h"
  #include "nvs_flash.h"
  #include "driver/gpio.h"
#endif

  
Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

SPIClass sd_spi(HSPI);

char GPSBuffer[150];
byte GPSIndex=0;
double gps_latitude = 0.0;
double gps_longitude = 0.0;
char lat_direction, lgt_direction;

uint8_t buf[]="Panda";
uint8_t len=5;

/*Wifi Udp Initialization
const char* ssid = "PacketReceiver"; // wifi ssid
const char* password = "ekalagamhsou"; //wifi password

const char* udpAddress = "192.168.43.204"; //destination IP

unsigned int udpPort=1234; //Server port

char pktbuf[10];//buffer to store udp data
char rx_val; //*not sure yet*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

WiFiUDP udp;
*/

void setup() {
  Serial.begin(115200);

  wifi_sniffer_init();
  
  pinMode(LED_GPIO_PIN, OUTPUT);

  Pressure_TemperatureInit();
}

void loop() {
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

  delay(1000);
}
