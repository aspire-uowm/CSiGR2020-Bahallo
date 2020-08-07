#include "GPS.h"

void parseNMEA(){
  char inByte;
  bool detect_new_line=false;
  
  while (!detect_new_line){
    
    if (gps_serial.available()) {
      inByte = gps_serial.read();
    
      // Serial.print(inByte); // Output exactly what we read from the GPS to debug    
      if ((inByte =='$') || (GPSIndex >= 150)){
        GPSIndex = 0;
      }      
      if (inByte != '\r' && inByte != '\n'){
        GPSBuffer[GPSIndex++] = inByte;
      }   
      if (inByte == '\n'){
        GPSBuffer[GPSIndex++] = '\0';
        detect_new_line=true;
      }
    }
  } 
  Serial.print("---->");
  Serial.println(GPSBuffer);
  // Serial.flush();
}

bool isGGA(){
  return (GPSBuffer[1] == 'G' && (GPSBuffer[2] == 'P' || GPSBuffer[2] == 'N') && GPSBuffer[3] == 'G' && GPSBuffer[4] == 'G' && GPSBuffer[5] == 'A');
}

//////////////////////////////////////////////////////////////////////////////////
//Convert NMEA latitude & longitude to decimal (Degrees)
//  Notice that for latitude of 0302.78469,
//              03 ==> degrees. counted as is
//              02.78469 ==> minutes. divide by 60 before adding to degrees above
//              Hence, the decimal equivalent is: 03 + (02.78469/60) = 3.046412
//  For longitude of 10601.6986,
//              ==> 106+1.6986/60 = 106.02831 degrees
//  Location is latitude or longitude
//  In Southern hemisphere latitude should be negative
//  In Western Hemisphere, longitude degrees should be negative
//////////////////////////////////////////////////////////////////////////////////

double degree_location(double loc, char loc_direction){
  double degLoc = 0.0;
  double degWhole= loc/100; // gives the whole degree part of latitude
  double degDec = (degWhole - ((int)degWhole)) * 100 / 60; // gives fractional part of location
  degLoc = (int)degWhole + degDec; // gives complete correct decimal form of location degrees
  
  if (loc_direction =='S' || loc_direction =='W') {  
    degLoc = (-1)*degLoc;
  }
  return degLoc;  
}

// GPGGA and GNGGA for the Ublox 8 series. Ex:
// no fix -> $GPGGA,,,,,,0,00,99.99,,,,,,*63
// fix    -> $GPGGA,171958.00,4903.61140,N,00203.95016,E,1,07,1.26,55.1,M,46.0,M,,*68 
void decodeGGA(){
  int i, j;
  char latitude[30], longitude[30];
  byte latIndex=0, lgtIndex=0;
  
  for (i=7, j=0; (i < GPSIndex) && (j<9); i++) { // We start at 7 so we ignore the '$GNGGA,'
    
    if (GPSBuffer[i] == ',')j++;    // Segment index
    else{
      if (j == 1){   // Latitude
        latitude[latIndex++]= GPSBuffer[i];
      }
      else if (j == 2){   // Latitude Direction: N=North, S=South
        lat_direction = GPSBuffer[i];
      }      
      else if (j == 3){    // Longitude
        longitude[lgtIndex++]= GPSBuffer[i];
      }
      else if (j == 4){   // Longitude Direction: E=East, W=West
        lgt_direction = GPSBuffer[i];
      }
    }
  }
  // Serial.print("Lat Direction: "); Serial.println(lat_direction);
  //Serial.print("Lgt Direction: "); Serial.println(lgt_direction);
  gps_latitude = degree_location(atof(latitude), lat_direction);
  gps_longitude = degree_location(atof(longitude), lgt_direction);
}

bool isValidLocation(){
  return (gps_latitude != 0.0 && gps_longitude != 0.0 && (lat_direction == 'N' || lat_direction=='S') && (lgt_direction=='E'|| lgt_direction=='W'));
}

void display_location(){
  Serial.println("==============");
  Serial.print("Location: ");
  Serial.print(gps_latitude, 5);
  Serial.print(",");
  Serial.println(gps_longitude, 5);
  Serial.println("=============="); 
}

void GPSinit(){
  //GPSserial.begin(9600, SERIAL_8N1, GPSTX, GPSRX);//format is baud, mode, UART RX data, UART TX data 
  gps_serial.begin(115200); 
}

double* GPSrun(){
  //while (GPSserial.available())Serial.write(GPSserial.read());  
  bool get_fix = false;
  
  if (!get_fix){
    parseNMEA();
    if (isGGA()){
      decodeGGA();
      if (isValidLocation()){ 
        get_fix = true;
        double coordinates[2] = {gps_latitude,gps_longitude};
        return coordinates;
        //display_location();
      }
    }
  }
}
