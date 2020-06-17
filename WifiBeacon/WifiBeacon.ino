<<<<<<< Updated upstream
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

=======
>>>>>>> Stashed changes
#include <ESP8266WiFi.h> // Wifi Connector

//BME/BMP280 specific
#include <Wire.h> // Wire Library
#include <Adafruit_Sensor.h> // Adafruit Sensor Library
#include <BME280I2C.h> // include BME280 Sensor (0x76)

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

// Changeable Stuff
// Sensorspecific
int sensorname = 4; // Sensor no. to differentiate results
long interval = 30000; // Interval at which to check data in ms (15min = 900000ms, 30sek = 30000ms) DONT CHECK FASTER THAN 2000ms! The BME/BMP will heat up or behave strangely!

// WiFi
char ssid[] = "XXX"; // Your Networkname
char pass[] = "XXX"; // Your Networkpassword

IPAddress ip(0, 0, 0, 0); // Ip of this device in your network
IPAddress gateway(0, 0, 0, 0); // Gateway this device looks for (The same IP as your router should work in most cases)
IPAddress subnet(255, 255, 255, 0); // Subnet this device looks for (255.255.255.0 should work in most cases)


// Do not change stuff below this line if you're not knowing what you're doing!
int wificonnect = 0; // checks the wificonnection 1 = connected
int connectloop = 0; // counts the number of tries

WiFiServer server(80);
WiFiClient client;
char query[128]; // max query length

long previousMillis = 0; // Will store the last time when sensors were read


float var_temp(NAN), var_hum(NAN), var_pres(NAN);

// Functionprototypes
void checksensor();
void wififunction();

// Runs once
void setup() {
  Serial.begin(115200);
  Wire.begin();
  //WiFi.persistent(false); // to fix unnecessary writing to flash and "random" connections to wifi, does not seem to work properly
  Serial.print("Sensor: ");
  Serial.println(sensorname);
  Serial.print(F("IP : "));
  Serial.println(ip);
  Serial.println("");
  Serial.println("AT+CWMODE_CUR=1<CR>"); // Sets ESP8266 as Client (avoids broadcasting a network)
  Serial.println("");
}
// Repeating code
void loop() {
  int i = 0;
  unsigned long currentMillis = millis();
  // run following code after each interval (ms)
  if (currentMillis - previousMillis > interval) {
    // saves the time at which it last measured
    previousMillis = currentMillis;


    do {
      checksensor(); // Tests which Sensor is currently connected

      // Sets the specific units, use Celsius or Fahrenheit here.
      // TODO: Move this into the "changeable lines"
      BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
      BME280::PresUnit presUnit(BME280::PresUnit_Pa);
      // reads sensordata
      bme.read(var_pres, var_temp, var_hum, tempUnit, presUnit);
      // Converts the input into useable variables
      char var_Ctemp[10];
      char var_Chum[10];
      char var_Cpres[20];
      dtostrf(var_temp, 1, 1, var_Ctemp);
      dtostrf(var_hum, 1, 1, var_Chum);
      dtostrf(var_pres, 1, 1, var_Cpres);
      // If the sensor functioned as it should
      if ((!isnan(var_hum)) && (!isnan(var_temp))) {
        Serial.println("Sensor has been read successfully");
        // TODO: Use the Pressuremeasurement to calculate the height etc.
        wififunction();
        // Sucks if you review your code after some time and didn't add comments..
      }
      connectloop = 0; // reset the variable for the next time this runs (used in wififunction())

      i++;
    } while ((!isnan(var_hum)) && (!isnan(var_temp)) && (i < 1));
    i = 0; // reset the loop for the next time this runs
    // disconnect wifi to save power
    wificonnect = 0; // reset the variable for the next time this runs (used in wififunction())
    WiFi.disconnect();
    Serial.println("Closed wifi connection");
    Serial.println("Waiting for the next loop...");
    Serial.println("");
    // TODO: use deepsleep
  }
  delay(20); // Workaround for an internal ESP8266 issue
}
void checksensor() {
  Serial.println("Searching for sensors...");
  //BME/BMP280
  while (!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  switch (bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      Serial.println("Found BME280 sensor! Success.");
      break;
    case BME280::ChipModel_BMP280:
      Serial.println("Found BMP280 sensor! No Humidity available.");
      break;
    default:
      Serial.println("Found UNKNOWN sensor! Error!");
  }
}
// Connect to WiFi
void wififunction() {
    if(WiFi.status() != 3 && WiFi.status() != 0){
    do {
    Serial.println("###WiFi NOT Connected##");
    WiFi.config(ip, gateway, subnet);
    Serial.println("Initialising connection");
    Serial.print(F("Setting static ip to : "));
    Serial.println(ip);
    Serial.println("");
    WiFi.mode(WIFI_STA); // Set WiFi to Clientmode
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    
    
    wificonnect = 1;
    connectloop++;

  } while ((wificonnect != 1) && (connectloop < 6)); // Aborts after 5 times to save power
  Serial.println("Wifi has been connected successfully");
  }
  else{
      Serial.println("###WiFi is Connected##");
    }
  Serial.println("");
  Serial.print("Assigned Hostname: ");
  Serial.println(WiFi.hostname());
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.println(WiFi.localIP());
}

#include <ESP8266WiFi.h> // Wifi Connector

//BME/BMP280 specific
#include <Wire.h> // Wire Library
#include <Adafruit_Sensor.h> // Adafruit Sensor Library
#include <BME280I2C.h> // include BME280 Sensor (0x76)

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

// Changeable Stuff
// Sensorspecific
int sensorname = 4; // Sensor no. to differentiate results
long interval = 30000; // Interval at which to check data in ms (15min = 900000ms, 30sek = 30000ms) DONT CHECK FASTER THAN 2000ms! The BME/BMP will heat up or behave strangely!

// WiFi
char ssid[] = "XXX"; // Your Networkname
char pass[] = "XXX"; // Your Networkpassword

IPAddress ip(0, 0, 0, 0); // Ip of this device in your network
IPAddress gateway(0, 0, 0, 0); // Gateway this device looks for (The same IP as your router should work in most cases)
IPAddress subnet(255, 255, 255, 0); // Subnet this device looks for (255.255.255.0 should work in most cases)


// Do not change stuff below this line if you're not knowing what you're doing!
int wificonnect = 0; // checks the wificonnection 1 = connected
int connectloop = 0; // counts the number of tries

WiFiServer server(80);
WiFiClient client;
char query[128]; // max query length

long previousMillis = 0; // Will store the last time when sensors were read


float var_temp(NAN), var_hum(NAN), var_pres(NAN);

// Functionprototypes
void checksensor();
void wififunction();

// Runs once
void setup() {
  Serial.begin(115200);
  Wire.begin();
  //WiFi.persistent(false); // to fix unnecessary writing to flash and "random" connections to wifi, does not seem to work properly
  Serial.print("Sensor: ");
  Serial.println(sensorname);
  Serial.print(F("IP : "));
  Serial.println(ip);
  Serial.println("");
  Serial.println("AT+CWMODE_CUR=1<CR>"); // Sets ESP8266 as Client (avoids broadcasting a network)
  Serial.println("");
}
// Repeating code
void loop() {
  int i = 0;
  unsigned long currentMillis = millis();
  // run following code after each interval (ms)
  if (currentMillis - previousMillis > interval) {
    // saves the time at which it last measured
    previousMillis = currentMillis;


    do {
      checksensor(); // Tests which Sensor is currently connected

      // Sets the specific units, use Celsius or Fahrenheit here.
      // TODO: Move this into the "changeable lines"
      BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
      BME280::PresUnit presUnit(BME280::PresUnit_Pa);
      // reads sensordata
      bme.read(var_pres, var_temp, var_hum, tempUnit, presUnit);
      // Converts the input into useable variables
      char var_Ctemp[10];
      char var_Chum[10];
      char var_Cpres[20];
      dtostrf(var_temp, 1, 1, var_Ctemp);
      dtostrf(var_hum, 1, 1, var_Chum);
      dtostrf(var_pres, 1, 1, var_Cpres);
      // If the sensor functioned as it should
      if ((!isnan(var_hum)) && (!isnan(var_temp))) {
        Serial.println("Sensor has been read successfully");
        // TODO: Use the Pressuremeasurement to calculate the height etc.
        wififunction();
        // Sucks if you review your code after some time and didn't add comments..
      }
      connectloop = 0; // reset the variable for the next time this runs (used in wififunction())

      i++;
    } while ((!isnan(var_hum)) && (!isnan(var_temp)) && (i < 1));
    i = 0; // reset the loop for the next time this runs
    // disconnect wifi to save power
    wificonnect = 0; // reset the variable for the next time this runs (used in wififunction())
    WiFi.disconnect();
    Serial.println("Closed wifi connection");
    Serial.println("Waiting for the next loop...");
    Serial.println("");
    // TODO: use deepsleep
  }
  delay(20); // Workaround for an internal ESP8266 issue
}
void checksensor() {
  Serial.println("Searching for sensors...");
  //BME/BMP280
  while (!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  switch (bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      Serial.println("Found BME280 sensor! Success.");
      break;
    case BME280::ChipModel_BMP280:
      Serial.println("Found BMP280 sensor! No Humidity available.");
      break;
    default:
      Serial.println("Found UNKNOWN sensor! Error!");
  }
}
// Connect to WiFi
void wififunction() {
    if(WiFi.status() != 3 && WiFi.status() != 0){
    do {
    Serial.println("###WiFi NOT Connected##");
    WiFi.config(ip, gateway, subnet);
    Serial.println("Initialising connection");
    Serial.print(F("Setting static ip to : "));
    Serial.println(ip);
    Serial.println("");
    WiFi.mode(WIFI_STA); // Set WiFi to Clientmode
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    
    
    wificonnect = 1;
    connectloop++;

  } while ((wificonnect != 1) && (connectloop < 6)); // Aborts after 5 times to save power
  Serial.println("Wifi has been connected successfully");
  }
  else{
      Serial.println("###WiFi is Connected##");
    }
  Serial.println("");
  Serial.print("Assigned Hostname: ");
  Serial.println(WiFi.hostname());
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.println(WiFi.localIP());
}
