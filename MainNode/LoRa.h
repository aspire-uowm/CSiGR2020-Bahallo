#include <Arduino.h>
#include <SPI.h>

#include <LoRa.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//866E6 for Europe
#define BAND 866E6

//initialize LoRa modulation
void LoRa_Init();

//run gps
void LoRa_Run(String message);
