#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WiFiUdp.h>

static WiFiUDP udp;

char* Udpssid = "Node"; // wifi ssid
char* Udppassword = '\0'; //wifi password

char* udpAddress = "192.168.43.155"; //destination IP
unsigned int udpPort=1234; //Server port

//byte mac[] = { 0xFE, 0xBB, 0x34, 0xE5, 0x29, 0xFC };

char pktbuf[10];//buffer to store udp data
//char rx_val;

char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

void UdpInit() {
  WiFi.begin(Udpssid,Udppassword);
  
  //things that happen until Wifi Connection is established:
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(5000);
    //ESP.restart(); 
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

void UdpRun() { 
  int packetSize=udp.parsePacket();
  if(!packetSize){
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
  }else{

    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
    int len = udp.read(incomingPacket, 255);
    if (len > 0)incomingPacket[len] = 0;
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
    
  }
}
