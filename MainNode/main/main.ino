/*  
 *   Arduino Tutorial - Testing the Adafruits BMP280 Presure & Temperature Sensor
 *   I2C Connection: Vin: 5V/3V, GND: GND, SCK: A5 (SCL), SDI: A4 (SDA) 
 *   Dev: Michalis Vasilakis // Date: 8/3/206 // Info: www.ardumotive.com    
*/
  
#include <Wire.h>
#include <SPI.h> //Why? Because library supports SPI and I2C connection
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Setup connection of the sensor
//Adafruit_BMP280 bmp;//I2C

//For SPI connection!
#define BMP_SCK 15
#define BMP_MISO 4//SD0
#define BMP_MOSI 2//SDI 
#define BMP_CS   0//


//Adafruit_BMP280 bme(BMP_CS);//hardware SPI
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);


//Variables
float pressure;   //To store the barometric pressure (Pa)
float temperature;//To store the temperature (oC)
int altimeter;    //To store the altimeter (m) (you can also use it as a float variable)

void setup() {
    Serial.begin(9600); //Begin serial communication at 9600bps
    
    while(!bmp.begin()){
      Serial.println("Error");
      delay(2000);
    }
    
    Serial.println("Adafruit BMP280 test:");
}

void loop() {
    
    //Read values from the sensor:
    pressure = bmp.readPressure();
    temperature = bmp.readTemperature();
    altimeter = bmp.readAltitude(1008); //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)
  
    //Print values to serial monitor:
    Serial.print(F("Pressure: "));
    Serial.print(pressure);
    Serial.print("Pa");

    Serial.print(F("Temp: "));
    Serial.print(temperature);
    Serial.print("oC");

    Serial.print(F("Altimeter: "));
    Serial.print(altimeter); // this should be adjusted to your local forcase
    Serial.println("m");
    
    delay(1000); //Update every sec
}
