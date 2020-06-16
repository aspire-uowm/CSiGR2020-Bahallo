#include "LoRa.h"

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
