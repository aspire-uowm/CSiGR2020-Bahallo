#include <Arduino.h>

#define gps_serial Serial

static char GPSBuffer[150];
static byte GPSIndex=0;
static double gps_latitude = 0.0;
static double gps_longitude = 0.0;
static char lat_direction, lgt_direction; 

//function to parse
void parseNMEA();

//function to check if valid
bool isGGA();

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
double degree_location(double loc, char loc_direction);

// GPGGA and GNGGA for the Ublox 8 series. Ex:
// no fix -> $GPGGA,,,,,,0,00,99.99,,,,,,*63
// fix    -> $GPGGA,171958.00,4903.61140,N,00203.95016,E,1,07,1.26,55.1,M,46.0,M,,*68 
void decodeGGA();

bool isValidLocation();

//function in order to display the stats ;)
void display_location();
void GPSinit();
double* GPSrun();
