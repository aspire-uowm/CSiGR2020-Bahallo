#include <WiFi.h>

char* servicesid = "Node_0";
char* password = '\0';

WiFiServer server(80);
IPAddress IP(192,168,2,20);
IPAddress mask = (255, 255, 255, 0);

void InitServer(){
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");

  WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(servicesid, password);
  WiFi.softAPConfig(IP, IP, mask);

  //IPAddress IP = WiFi.softAPIP();
  //Serial.print("AP IP address: " + IP);
  
  server.begin();

  Serial.println("Server started.");
  Serial.println("IP: " + WiFi.softAPIP());
  Serial.println("MAC: " + WiFi.softAPmacAddress());
}

void displayInfo(WiFiClient client){
    Serial.println("From the station: " + client.readStringUntil('\r'));
    client.flush();
    
    Serial.print("Byte sent to the station: ");
    Serial.println(client.println("RSSI?" + '\r'));
}

String Listen(){

  WiFiClient client = server.available();// Listen for incoming clients

  if(!client)return "\0";
  
  if(client.connected()){
    if(client.available())Serial.write(client.read());  
    client.stop();
    displayInfo(client);
    
    return client.readStringUntil('\r');
  }else return "\0";
}
