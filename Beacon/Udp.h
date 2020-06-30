#include <WiFi.h>
#include <WiFiUdp.h>

static WiFiUDP udp;

char* Udpssid = "Node"; // wifi ssid
char* Udppassword = '\0'; //wifi password

char* udpAddress = "192.168.43.155"; //destination IP
unsigned int udpPort=1234; //Server port

byte mac[] = { 0xFE, 0xBB, 0x34, 0xE5, 0x29, 0xFC };

char pktbuf[10];//buffer to store udp data
char rx_val;

void UdpInit() {
  WiFi.begin(Udpssid,Udppassword);
  
  //things that happen until Wifi Connection is established:
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    //ESP.restart(); 
  }
  
  //after Connection is established:
  Serial.println(WiFi.localIP()); //prints wifi ip to console
  Serial.println("Status: Connected");

  //Enable udp
  udp.begin(udpPort);
  Serial.println(udpPort);

}

void UdpRun() { 
  int rp1=udp.parsePacket();
  if(!rp1){
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
