#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/*
 * #define BMP_SCK 13
 * #define BMP_MISO 12
 * #define BMP_MOSI 11
 * #define BMP_CS 10
 */

static Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

//initialize the BMP280 Breakout board
void Pressure_TemperatureInit();

//Get
void Pressure_TemperatureRun();
