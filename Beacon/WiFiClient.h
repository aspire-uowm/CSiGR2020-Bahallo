#include <ESP8266WiFi.h>

IPAddress server(192,168,2,20);// IP address of the AP
WiFiClient client;

char* password = '\0';// SERVER PASSWORD
String Devicename = "Beacon";

void CheckandConnect(char* ssid){

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);// connects to the WiFi AP
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("Connected");
  Serial.println("LocalIP: " + WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.println("Gateway: " + WiFi.gatewayIP());
  Serial.println("AP MAC: " + WiFi.BSSIDstr());
}

void printServer(/*String msg*/){
  client.connect(server,80);
  
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print(WiFi.RSSI()+'\r'));
  
  Serial.println("From the AP: " + client.readStringUntil('\r'));
  
  client.flush();
  client.stop();
}
