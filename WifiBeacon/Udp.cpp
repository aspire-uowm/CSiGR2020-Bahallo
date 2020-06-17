#include "Udp.h"

void WiFiUdp_Init(){
  WiFi.begin(ssid, password);
  
    //things that happen until Wifi Connection is established:
    while (WiFi.waitForConnectResult() != WL_CONNECTED) 
    {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart(); 
    }
  
    //after Connection is established:
    Serial.println(WiFi.localIP()); //prints wifi ip to console
    Serial.println("Status: Connected");

    //Enable udp
    udp.begin(udpPort);
    Serial.println(udpPort);
  }

WiFiUdp_Run(){
  int rp1=udp.parsePacket();
  if(!rp1)
  {
     //if lora is occupied:
    if(Serial.available() > 0) 
    {
      rx_val = Serial.read(); //not sure!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      Serial.print("udp_send: ");
      Serial.println(rx_val);
      udp.beginPacket(udpAddress, udpPort);
      udp.write(rx_val);
      udp.endPacket();
    }
  }
}
