#include <LoRa.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BAND 866E6

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  Serial.println("LoRa Receiver starting");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  while(!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // put your main code here, to run repeatedly:
  String packet = "";
  int packetSize = LoRa.parsePacket();


  if( packetSize ) {
      while ( LoRa.available()){
         packet = LoRa.readString();
      }
      Serial.print(packet);
  }
  /*
  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);*/

}
