#include "ttnModule.h"

void ttnDeviceInit(){
  
  loraSerial.begin(57600);
  debugSerial.begin(9600);
}

void ttnDevice_get(){
  
  debugSerial.println("Device Information");
  debugSerial.println();
  ttn.showStatus();
  debugSerial.println();
  debugSerial.println("Use the EUI to register the device for OTAA");
  debugSerial.println("-------------------------------------------");
  debugSerial.println();

  delay(10000);
}
