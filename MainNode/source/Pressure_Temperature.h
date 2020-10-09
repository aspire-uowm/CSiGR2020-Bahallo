#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/*
 * #define BMP_SCK 13
 * #define BMP_MISO 12
 * #define BMP_MOSI 11
 * #define BMP_CS 10
 */

static Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

//initialize the BMP280 Breakout board
void Pressure_TemperatureInit(){
  Serial.println(F("BMP280 test"));
 
  while (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }
}

//Get
void PrTemAltPrint(){
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
 
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
 
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");   
}

float* getPrTemAlt(){
  float values[3] = {bmp.readTemperature(),bmp.readPressure(),bmp.readAltitude(1013.25)};
  return values;
}
