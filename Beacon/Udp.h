#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

char* ssid = "Node_0";// SERVER WIFI NAME
char* password = '\0';// SERVER PASSWORD
String Devicename = "Beacon";

unsigned int UDPPort = 1234;  

char result[16];
char packetBuffer[255];// buffer for incoming data

void Check_WiFi_and_Connect(){
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(UDPPort);
  Serial.printf(
    "Now listening at IP %s, UDP port %d\n",
    WiFi.localIP().toString().c_str(), UDPPort
  );
}

void Send_Data_To_Server(){
  int packetSize = Udp.parsePacket();
  
  if (packetSize){
    // receive incoming UDP packets
    Serial.printf(
      "Received %d bytes from %s, port %d\n",
      packetSize, Udp.remoteIP().toString().c_str(),
      Udp.remotePort()
    );
    int len = Udp.read(packetBuffer, 255);
    //if (len > 0)packetBuffer[len] = 0;
    
    Serial.printf("UDP packet contents: %s\n", packetBuffer);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("Panda"/*packetBuffer*/);
    Udp.endPacket();
    delay(500);
  }
}
