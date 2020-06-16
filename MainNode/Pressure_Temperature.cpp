#include "Pressure_Temperature.h"

void Pressure_TemperatureInit(){
  
  Serial.println(F("BMP280 test"));
 
  while (!bme.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }  
}

void Pressure_TemperatureRun(){
  
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
 
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");
 
  Serial.print("Approx altitude = ");
  Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");  
}
