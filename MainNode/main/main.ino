#include <LoRa.h>

#define SendToBase(STR) LoRa.beginPacket();LoRa.print(STR);LoRa.endPacket();

//definig protocol pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BAND 866E6//for Europe ;)

void setup() {
  Serial.begin(115200);//setting baudrate

  Serial.print("Setup Start...");
  //SPI.begin(SCK, MISO, MOSI, SS); //pin initializaton
  LoRa.setPins(SS, RST, DIO0);//LoRa module initialization

  //wait until Lora initialization
  while (!LoRa.begin(BAND))Serial.println("Starting LoRa failed!");

  Serial.println("LoRa Initializing OK!");
  delay(200);
}

void loop() {
  Serial.print("Sending packet: ");

  //Send LoRa packet to receiver
  SendToBase("Hello!");
  
  delay(2000);
}
