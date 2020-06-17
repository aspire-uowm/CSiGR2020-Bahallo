#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "PacketReceiver"; // wifi ssid
const char* password = "ekalagamhsou"; //wifi password

const char* udpAddress = "192.168.43.155"; //destination IP
WiFiUDP udp;
unsigned int udpPort=1234; //Server port

char pktbuf[10];//buffer to store udp data
char rx_val;
void setup() 
{
  Serial.begin(115200);
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

void loop() 
{
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
