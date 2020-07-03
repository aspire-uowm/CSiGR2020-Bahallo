#include <Servo.h>
#include "Udp.h"
#include "BMP.h"

#define motorPin 2
#define runMotor(from,msecs,to) servo.write(from);delay(msecs);servo.write(to)

Servo servo; 

char *NodeNames[] = {"Node_0","Node_1","Node_2"};

void setup() {
  Serial.begin(115200);
 
  //servo.attach(motorPin);
  //BMPInit();

  Check_WiFi_and_Connect(NodeNames[0]);

  //runMotor(0,200,90); 
}

void loop() {
  //for(int i=0;i<3; i++)Check_WiFi_and_Connect(NodeNames[i]);
  Send_Data_To_Server();
  
  //delay(10000);
  //if(bmp.readAltitude(1019.66) < 55)runMotor(90,500,0);
}
