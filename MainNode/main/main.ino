#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN                     5
#define WIFI_CHANNEL_SWITCH_INTERVAL  (500)
#define WIFI_CHANNEL_MAX               (1)

uint8_t level = 0, channel = 7;

static wifi_country_t wifi_country = {.cc="GR", .schan = 7, .nchan = 7}; //Most recent esp32 library struct

static void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type){
  if (type != WIFI_PKT_MGMT)return;

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
  printf("CHAN=%02d, RSSI=%02d\n",ppkt->rx_ctrl.channel,ppkt->rx_ctrl.rssi);
}

static esp_err_t event_handler(void *ctx, system_event_t *event){return ESP_OK;}

static void wifi_sniffer_init(void){
  
  nvs_flash_init();
  tcpip_adapter_init();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  ESP_ERROR_CHECK( esp_wifi_set_country(&wifi_country) ); /* set country for channel range [1, 13] */
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_NULL) );
  ESP_ERROR_CHECK( esp_wifi_start() );
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  wifi_sniffer_init();
  
  pinMode(LED_GPIO_PIN, OUTPUT);
}

void loop() {
  //Serial.print("inside loop");
  delay(1000); // wait for a second
  
  if (digitalRead(LED_GPIO_PIN) == LOW)digitalWrite(LED_GPIO_PIN, HIGH);
  else digitalWrite(LED_GPIO_PIN, LOW);
  vTaskDelay(WIFI_CHANNEL_SWITCH_INTERVAL / portTICK_PERIOD_MS);
  //wifi_sniffer_set_channel(channel);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}
