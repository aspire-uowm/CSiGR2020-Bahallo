#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

uint8_t level = 0, channel = 7;

 //Most recent esp32 library struct
static wifi_country_t wifi_country = {.cc="GR", .schan = 7, .nchan = 7};

void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type);//now thats what I'm talking about

//it handles events but how does it fail?
static esp_err_t event_handler(void *ctx, system_event_t *event);

static void wifi_sniffer_init(void);
