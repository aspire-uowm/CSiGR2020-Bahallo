#include <Wire.h> // Wire Library
#include <Adafruit_Sensor.h> // Adafruit Sensor Library
#include <BME280I2C.h> // include BME280 Sensor (0x76)

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,
