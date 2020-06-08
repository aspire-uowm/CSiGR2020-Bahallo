//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//include gps lib
#include <TinyGPS++.h> 
#include <HardwareSerial.h>

#include "_defines.h"
#include "_global.h"
#include "dev_gps.h"

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//866E6 for Europe
#define BAND 866E6

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  
  //Setup Lora
  //initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("LoRa Sender Test");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  
  //Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  //Test Lora if Begins
  while (!LoRa.begin(BAND)) 
  {
    Serial.println("Starting LoRa failed!");
  }
  Serial.println("LoRa Initializing OK!");

  #ifdef DEBUG
  Serial.println("=====================================");
  Serial.print(FILENAME);
  Serial.print(" compiled: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  Serial.println("Hardware: ESP32, Neo 6m gps conected by serial");
  Serial.println("pins on ESP32 rx=16, tx=18");
  Serial.println("Libraries TinyGPS++.h and HardwareSerial.h");
  Serial.println("by Vicente Niclos 2019");
  Serial.println("=====================================");
  #endif

  fncDev_Gps_setup();
  delay(2000);
}

void loop() 
{
 while (.available() > 0)
 {
    if (gps.encode(gpsSerial.read()))
    {
      displayInfo();
      delay(2000);
    }
 }
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  while (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
  }
    fncDev_Gps_Loop_IsInterval();
}




/*void displayInfo()
{
  Lora.beginPacket();
  if (gps.location.isValid())
  {
    // Print Latitude
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6); 
    Lora.print(gps.location.lat(), 6);
    
    // Print Longitude
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6); 
    Lora.print(gps.location.lng(), 6); 

    // Print Altitude
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    Lora.print(gps.altitude.meters()); 
    
    
    // Speed in meters per second
    Serial.print("Speed m/s: ")
    Serial.println(gps.speed.mps()); 
    Lora.print(gps.speed.mps()); 
  }
  // Error check
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    // Print the day
    Serial.println(gps.date.day());
    Lora.print(gps.date.day());

    // Print the month
    Serial.print("/");
    Serial.println(gps.date.month()); 
    Lora.print(gps.date.month()); 
    
    //Print the year
    Serial.print("/");
    Serial.println(gps.date.year());   
    Lora.print(gps.date.year());   
  }
  // Error Check
  else
  {
    Serial.println("Date Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)  
    {
        Serial.print(F("0"));
    }
    //Print Hours
    Serial.print(gps.time.hour()); 
    Lora.print(gps.time.hour()); 
    
    Serial.print(":");
    
    if (gps.time.minute() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print minutes
    Serial.print(gps.time.minute()); 
    Lora.print(gps.time.minute()); 
    
    Serial.print(":");
    
    if (gps.time.second() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print seconds
    Serial.print(gps.time.second()); 
    Lora.print(gps.time.second());
    
    Serial.print(".");
    
    if (gps.time.centisecond() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print centiseconds
    Serial.println(gps.time.centisecond()); 
    Lora.print(gps.time.centisecond()); 
    
  }
  //Error check
  else
  {
    Serial.println("Minute Not Available");
  }

  Serial.println("");
  Serial.println("");
  
  Lora.endPacket();
}*/
  
