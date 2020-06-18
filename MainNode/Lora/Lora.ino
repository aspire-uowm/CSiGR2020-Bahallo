#include <LoRa.h>
#include <SPI.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//866E6 for Europe
#define BAND 866E6

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  Serial.println("LoRa Receiver starting");

  //LoRa.setPins(18,14,26);

  //SPI LoRa pins
  //SPI.begin(SCK, MISO, MOSI, SS);
  SPI.begin();
  
  //Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  while(!LoRa.begin(BAND)){
      Serial.println("Could not find a valid LoRa transceiver, check pins used and wiring!");
      delay(100);  
  }Serial.print("All good, ready!!");
}

void loop() {
  // put your main code here, to run repeatedly:

  LoRa.beginPacket();

  LoRa.print("Hello World");

  LoRa.endPacket();

  LoRa.sleep();
}
