#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp; // Creation of wifi Udp instance

char packetBuffer[255];

unsigned int localPort = 1234;

const char *ssid = "Node_0";  
const char *password = '\0';

void UdpInit(){
  
  WiFi.softAP(ssid, password);  // ESP-32 as access point
  Udp.begin(localPort);
}

void GetUdpackets(){
  int packetSize = Udp.parsePacket();
  
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len-1] = 0;
    Serial.print("Recibido(IP/Size/Data): ");
    Serial.print(Udp.remoteIP());Serial.print(" / ");
    Serial.print(packetSize);Serial.print(" / ");
    Serial.println(packetBuffer);

    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.printf("received: ");
    Udp.printf(packetBuffer);
    Udp.printf("\r\n");
    Udp.endPacket();
  }
}
