#include <Servo.h>

#include "WiFiClient.h"
#include "BMP.h"

#define motorPin 2
#define runMotor(from,msecs,to) servo.write(from);delay(msecs);servo.write(to)

#define rdAlt 1010  /* !!!!! Adjusted to local forecast !!!!! */
int flag = 0, height_lock = 800 , height_brake = 70;

  
Servo servo; 

char *NodeNames[] = {"Node_0","Node_1","Node_2"};

void setup() 
{
  Serial.begin(115200);
 
  servo.attach(motorPin);
  BMPInit();

  CheckandConnect(NodeNames[0]);

}

void loop() 
{
  //for(int i=0;i<3; i++)Check_WiFi_and_Connect(NodeNames[i]);
  Send_Data_To_Server();

  if(i == 0)                  //Check if Servo just started
  {
    delay(5000); 
    runMotor(90,500,0);       //Servo Turns in 90
    flag = 1;                 //Servo Lock
  }
  
  if (bmp.readAltitude(rdAlt) > ( /*height*/ + height_lock))
  {
    flag = 2;                 //Servo Armed  
  }
  
  if(bmp.readAltitude(rdAlt) <= ( /*height*/ + height_brake) )
  {
    if(flag == 2)             //Check if Servo is Armed
    {
      runMotor(90,500,0);     //Servo Turns in 0
      delay(5000);            
    }
  }
  
  printServer("Hello!\r");
}
