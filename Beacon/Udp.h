#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include <WiFiUdp.h>
//#include <WiFiUDP.h>

WiFiUDP udp;

char* Udpssid[] = {"Node_0","Node_1","Node_2"}; // wifi ssid
char* Udppassword = '\0'; //wifi password
const String  Devicename = "Beacon";

char* udpAddress = "192.168.43.155"; //destination IP
unsigned int udpPort = 1234; //Server port

// WIFI Module Role & Port    
IPAddress APlocal_IP(192, 168, 4, 1);
IPAddress    apIP(10, 10, 10, 1);

IPAddress APgateway(192, 168, 4, 1);
IPAddress APsubnet(255, 255, 255, 0);

//byte mac[] = { 0xFE, 0xBB, 0x34, 0xE5, 0x29, 0xFC };

char pktbuf[10];//buffer to store udp data
char replyPacket[] = "Hi there! Got the message :-)";

void UdpInit(char* ssid) {
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,Udppassword);
  
  //things that happen until Wifi Connection is established:
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(5000);
    //ESP.restart();
    WiFi.disconnect();// probably not necessary due to WiFi.status() != WL_CONNECTED
    WiFi.begin("DataTransfer"); 
  }Serial.println("Good");
  
  //after Connection is established:
  Serial.println(WiFi.localIP()); //prints wifi ip to console
  Serial.println("Status: Connected");

  //Enable udp
  udp.begin(udpPort);
  Serial.printf(
    "Now listening at IP %s, UDP port %d\n",
    WiFi.localIP().toString().c_str(), udpPort
  );
}

void UdpRun(){

  //unsigned long tNow;
    
  //tNow=millis();// get the current runtime
  //dtostrf(tNow, 8, 0, result);// translate it to a char array.

  int packetSize = udp.parsePacket();
  if(!packetSize){
     //if lora is occupied:
    if(Serial.available() > 0) {
      
      char rx_val = Serial.read();
      Serial.print("udp_send: ");
      Serial.println(rx_val);
      
      udp.beginPacket(udpAddress, udpPort);
      udp.write(rx_val);
      udp.endPacket();
    }
  }else{// receive incoming UDP packets
    
     Serial.printf(
       "Received %d bytes from %s, port %d\n",
       packetSize, udp.remoteIP().toString().c_str(),
       udp.remotePort()
     );
     
     int len = udp.read(pktbuf, 255);
     if (len > 0)pktbuf[len] = 0;
     Serial.printf("UDP packet contents: %s\n", pktbuf);

     // send back a reply, to the IP address and port we got the packet from
     udp.beginPacket(udp.remoteIP(), udp.remotePort());
     udp.write(replyPacket);
     udp.endPacket();
  }
}
