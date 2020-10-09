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
#define BAND 433E6//866E6

//initialize LoRa modulation
void LoRa_Init(){
   //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  
  //Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  //Test Lora if Begins
  while (!LoRa.begin(BAND))Serial.println("Starting LoRa failed!");
  
  Serial.println("LoRa Initializing OK!");
}

void LoRa_Run(String message){  
  LoRa.beginPacket();
  LoRa.print(message); 
  LoRa.endPacket();
}
