#include <Servo.h>
#include "Udp.h"
#include "BMP.h"

#define motorPin 2
#define runMotor(from,msecs,to) servo.write(from);delay(msecs);servo.write(to)

Servo servo; 

void setup() {
  Serial.begin(115200);
 
  servo.attach(motorPin);
  BMPInit();

  UdpInit("Node_0");

  runMotor(0,200,90); 
}

void loop() {
  
/*
* for(int i=0; i<3; i++){
*   UdpInit(Udpssid[i]);
*   delay(500);
* }
*/
  UdpRun();
  
  delay(10000);
  if(bmp.readAltitude(1019.66) < 55)runMotor(90,500,0);
}
