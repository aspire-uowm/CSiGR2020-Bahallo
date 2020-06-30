#include <Servo.h>
#include "Udp.h"

#define motorPin 3
#define runMotor(msecs,ang) servo.write(0);delay(msecs);servo.write(ang)

Servo servo; 

void setup() {
  Serial.begin(115200);
 
  servo.attach(motorPin); 
}

void loop() {
  delay(1000);
  runMotor(500,90);
}
