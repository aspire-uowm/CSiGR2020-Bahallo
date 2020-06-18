//Libraries for LoRa
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

void setup() {
  
  //Setup Lora
  //initialize Serial Monitor
  Serial.begin(115200);
  Serial.println("LoRa Sender Test");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  
  //Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  //Test Lora if Begins
  while (!LoRa.begin(BAND)) {
    
    Serial.println("Starting LoRa failed!");
  }Serial.println("LoRa Initializing OK!");

  delay(2000);
}

void loop() 
{
    LoRa.beginPacket();
    
    LoRa.print("Bahhalo");
    
    LoRa.endPacket();
}  
