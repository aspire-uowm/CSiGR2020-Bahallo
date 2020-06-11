void displayInfo(TinyGPSPlus gps)
{
  
  if (gps.location.isValid())
  {
    // Print Latitude
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6); 
    
    // Print Longitude
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6); 
    Lora.print(gps.location.lng(), 6); 

    // Print Altitude
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    Lora.print(gps.altitude.meters()); 
    
    
    // Speed in meters per second
    Serial.print("Speed m/s: ")
    Serial.println(gps.speed.mps()); 
    Lora.print(gps.speed.mps()); 
  }
  // Error check
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    // Print the day
    Serial.println(gps.date.day());
    Lora.print(gps.date.day());

    // Print the month
    Serial.print("/");
    Serial.println(gps.date.month()); 
    Lora.print(gps.date.month()); 
    
    //Print the year
    Serial.print("/");
    Serial.println(gps.date.year());   
    Lora.print(gps.date.year());   
  }
  // Error Check
  else
  {
    Serial.println("Date Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)  
    {
        Serial.print(F("0"));
    }
    //Print Hours
    Serial.print(gps.time.hour()); 
    Lora.print(gps.time.hour()); 
    
    Serial.print(":");
    
    if (gps.time.minute() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print minutes
    Serial.print(gps.time.minute()); 
    Lora.print(gps.time.minute()); 
    
    Serial.print(":");
    
    if (gps.time.second() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print seconds
    Serial.print(gps.time.second()); 
    Lora.print(gps.time.second());
    
    Serial.print(".");
    
    if (gps.time.centisecond() < 10) 
    {
        Serial.print(F("0"));
    }
    //Print centiseconds
    Serial.println(gps.time.centisecond()); 
    Lora.print(gps.time.centisecond()); 
    
  }
  //Error check
  else
  {
    Serial.println("Minute Not Available\n\n");
  }
  
  Lora.endPacket();
}
