#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface

void BMPInit(){
  
  Serial.println(F("BMP280 test"));

  while (!bmp.begin()) 
  {
    Serial.println(F("Could not find a valid BMP280 sensor"));
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
