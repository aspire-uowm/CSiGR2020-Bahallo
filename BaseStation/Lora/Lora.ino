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
  //SPI.begin(SCK, MISO, MOSI, SS);
  SPI.begin();
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  while(!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      Serial.print(LoRa.readString());
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);
  }
}
