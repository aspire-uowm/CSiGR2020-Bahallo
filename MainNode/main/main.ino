#include <LoRa.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN                     5
#define WIFI_CHANNEL_SWITCH_INTERVAL  (500)
#define WIFI_CHANNEL_MAX               (1)

uint8_t level = 0, channel = 7;
#define SendToBase(STR) LoRa.beginPacket();LoRa.print(STR);LoRa.endPacket();

//definig protocol pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

static wifi_country_t wifi_country = {.cc="GR", .schan = 7, .nchan = 7}; //Most recent esp32 library struct

void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type){ //if packet is type of "MGMT" casts data to wifi_promiscuous_pkt_t * and prints channel and rssi of them
  if (type != WIFI_PKT_MGMT)return;

  if (digitalRead(LED_GPIO_PIN) == LOW)digitalWrite(LED_GPIO_PIN, HIGH);
  else digitalWrite(LED_GPIO_PIN, LOW);
  
  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
  printf("CHAN=%02d, RSSI=%02d\n",ppkt->rx_ctrl.channel,ppkt->rx_ctrl.rssi);
  LoRa.print("Main 1: "+ppkt->rx_ctrl.rssi);
  Serial.println("Main 1: "+ppkt->rx_ctrl.rssi);
}

static esp_err_t event_handler(void *ctx, system_event_t *event){return ESP_OK;}//it handles events but how does it fail?

static void wifi_sniffer_init(void){
  nvs_flash_init();
  tcpip_adapter_init();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );//runs a loop of handling events...needs more research
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );//checks if wifi init has Allocated resource for WiFi driver & has started the wifi task successfully
  ESP_ERROR_CHECK( esp_wifi_set_country(&wifi_country) ); /* set country for channel range [1, 13] */
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );//checks if WiFi API is set successfully to store to ram.// should do WIFI_STORAGE_FLASH for saving in ram and sd(memory and flash)
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_NULL) );//checks if WiFi is set successfully to null mode.
  ESP_ERROR_CHECK( esp_wifi_start() );//checks if wifi can be started according to data we set
  esp_wifi_set_promiscuous(true);//enables promiscuous mode (meaning that receiver also analyzes data of packets instead of only receiving and tranfering them 
  esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler);//whenever a package is received , promiscuous data are given to the parameter function 
}

void setup(){
  Serial.begin(115200);
  delay(10);
  
  wifi_sniffer_init();
  
  pinMode(LED_GPIO_PIN, OUTPUT);
}

void loop(){
  //Serial.println("inside loop");
  delay(500); // wait for a second
  
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}
