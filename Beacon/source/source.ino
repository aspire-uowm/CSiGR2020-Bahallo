#include <Servo.h>

#include "WiFiAP.h"
#include "WiFiClient.h"
#include "BMP.h"

#define motorPin 2
#define runMotor(from,msecs,to) servo.write(from);delay(msecs);servo.write(to)

#define rdAlt 1010  /* Adjusted to local forecast ! */
#define Height 70

bool flag = false;
int i=0;

Servo servo; 

char *NodeNames[] = {"Node_0","Node_1","Node_2"};

void setup() {
  
  Serial.begin(115200);
 
  //servo.attach(motorPin);
  //BMPInit();

  CheckandConnect(NodeNames[0]);
  //APsetup();

  //runMotor(0,200,90);//lock the bahallo into place 
}

void loop() {

  //CheckandConnect(NodeNames[i++%3]);
  
  //if ((bmp.readAltitude(rdAlt) < Height) && flag ) {runMotor(90,500,0);}
  //else flag = bmp.readAltitude(rdAlt) > Height;

  delay(1000);
  printServer(/*"Hello!\r"*/);
  //createAPs();
}
