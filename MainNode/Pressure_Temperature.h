#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

//initialize the BMP280 Breakout board
void Pressure_TemperatureInit();

//Get
void Pressure_TemperatureRun();
