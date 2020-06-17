#include <LoRa.h>
#include <iostream>
#include <fstream>
using namespace std;

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  Serial.println("LoRa Receiver starting");

  LoRa.setPins(18,14,26);

  if(!LoRa.begin(868E6)){
      Serial.println("Could not find a valid LoRa transceiver, check pins used and wiring!");
      delay(100);  
  }
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

  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();

}
