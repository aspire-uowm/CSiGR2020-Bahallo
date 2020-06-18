#include <WiFi.h>
#include <WiFiUdp.h>

//Wifi Udp Initialization

const char* ssid = "PacketReceiver"; // wifi ssid
const char* password = "ekalagamhsou"; //wifi password

const char* udpAddress = "192.168.43.204"; //destination IP

unsigned int udpPort=1234; //Server port

char pktbuf[10];//buffer to store udp data
char rx_val; //*not sure yet*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

WiFiUDP udp;

void WiFi_UdpInit(){
  
  WiFi.begin(ssid, password);
  
  //things that happen until Wifi Connection is established:
  while (WiFi.waitForConnectResult() != WL_CONNECTED){
    
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

void WiFi_UdpRun(){
  
  if(!udp.parsePacket()){//checks for udp packets
    
    //if lora is occupied:
    if(Serial.available() > 0){
      
      rx_val = Serial.read(); //not sure!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      Serial.print("udp_send: ");
      Serial.println(rx_val);
      udp.beginPacket(udpAddress, udpPort);
      udp.write(rx_val);
      udp.endPacket();
    }else{
      
      udp.read(pktbuf, 1);
      Serial.print("Packet from " + String(udpAddress) + ": ");
      Serial.println(pktbuf);
      delay(1000); 
    } 
  }
  
}
