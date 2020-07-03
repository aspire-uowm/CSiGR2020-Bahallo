#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp; // Creation of wifi Udp instance

char packetBuffer[255];

unsigned int port = 1234;

const char *ssid = "Node_0";  
const char *password = '\0';

void UdpInit(){
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid, password); // ESP-32 as access point
  Udp.begin(port);
}

void GetUdpackets(){
  int packetSize = Udp.parsePacket();
  
  if (packetSize){
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len-1] = 0;
    Serial.print("Grabed (IP/Size/Data): ");
    Serial.println(Udp.remoteIP());
    Serial.println(packetSize);
    Serial.println(packetBuffer);

    /*Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.printf("received: ");
    Udp.printf(packetBuffer);
    Udp.printf("\r\n");
    Udp.endPacket();
    */
  }else Serial.print('.');
}
