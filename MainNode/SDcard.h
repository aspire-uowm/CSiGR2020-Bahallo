#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "defines.h"

/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      14
 *    VSS      GND
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */

SPIClass sd_spi(HSPI);

uint8_t buf[]="Panda";
uint8_t len=5;

//initialize te on board sdcard pins
void SDcard_Init();

//Write to sdcard file
void SDcard_Run();
