#define NEO6M_RX_PIN 1 // board TX --> neo6m RX
#define NEO6M_TX_PIN 3 // board RX --> neo6m TX

#define GPSBAUD 9600          //this is the serial baud rate that will be used for the GPS, a common default

#define GPSTX 3              //pin number for TX output from Arduino - RX into GPS
#define GPSRX 1              //pin number for RX input into Arduino - TX from GPS

#define GPSserial Serial2     //define GPSserial as ESP32 Serial2 

void setup()
{
  
  GPSserial.begin(9600, SERIAL_8N1, GPSTX, GPSRX);           //format is baud, mode, UART RX data, UART TX data 
                                                                 
  Serial.begin(115200);
  Serial.println("26_GPS_Echo_ESP32 Starting");
}

void loop()
{
  while (GPSserial.available())
  {
    Serial.write(GPSserial.read());
  }
}
