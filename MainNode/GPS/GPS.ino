//include gps lib
#include <TinyGPS++.h> 
#include <HardwareSerial.h>

#include "_defines.h"
#include "_global.h"
#include "dev_gps.h"

// Create a TinyGPS++ object
TinyGPSPlus gps;

//HardwareSerial g_device_GpsSerial(1);  // gps  recive data by uart

void setup(){

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

  g_device_GpsSerial.begin(9600, SERIAL_8N1, 3, 1);
  
}

void loop(){

  while (g_device_GpsSerial.available() > 0)
 {
    if (gps.encode(g_device_GpsSerial.read()))
    {
     displayInfo();//does not work needs figuring out
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
