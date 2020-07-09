#include <Servo.h>

#include "WiFiClient.h"
#include "BMP.h"

#define motorPin 2
#define runMotor(from,msecs,to) servo.write(from);delay(msecs);servo.write(to)

#define rdAlt 1010  /* Adjusted to local forecast ! */
#define Height 70

bool flag = false;
  
Servo servo; 

char *NodeNames[] = {"Node_0","Node_1","Node_2"};

void setup() 
{
  Serial.begin(115200);
 
  servo.attach(motorPin);
  BMPInit();

  CheckandConnect(NodeNames[0]);

  runMotor(0,200,90); 
}

void loop() 
{
  //for(int i=0;i<3; i++)Check_WiFi_and_Connect(NodeNames[i]);
  //Send_Data_To_Server();

  if((bmp.readAltitude(rdAlt) < 70) && flag) runMotor(90,500,0);
  else flag = !(bmp.readAltitude(rdAlt) > 70) && flag;
  
  printServer("Hello!\r");
}
