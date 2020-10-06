#include <Arduino.h>

#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define WIFI_CHANNEL_SWITCH_INTERVAL  (500)
#define WIFI_CHANNEL_MAX               (1)

#define LED_GPIO_PIN 5

#ifdef __cplusplus
  extern "C" {
#endif

    static uint8_t level = 0, channel = 7;

    //Most recent esp32 library struct
    static wifi_country_t wifi_country = {.cc="GR", .schan = 7, .nchan = 7};

    void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type);//now thats what I'm talking about

    //it handles events but how does it fail?
    static esp_err_t event_handler(void *ctx, system_event_t *event);

    void wifi_sniffer_init(void);

#ifdef __cplusplus
  }
#endif
