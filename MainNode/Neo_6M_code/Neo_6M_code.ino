#define NEO6M_RX_PIN D2 // board D2 --> neo6m TX
#define NEO6M_TX_PIN D3 // board D3 --> neo6m RX

#include <TinyGPS++>

static TinyGPSPlus gpsParser;
static TinyGPSPlus emptyGpsParser;
static SoftwareSerial gpsSerial(NEO6M_RX_PIN, NEO6M_TX_PIN);

void Neo6m::setup()
{
    Serial.print("Setting up Neo-6M GPS module... ");
    gpsSerial.begin(NEO6M_BAUD);
    Serial.println("done");
}

TinyGPSPlus Neo6m::read()
{
    while (gpsSerial.available() > 0)
        if (gpsParser.encode(gpsSerial.read()))
            return gpsParser;

    return emptyGpsParser;
}

void Neo6m::print(TinyGPSPlus gpsParser)
{
    if (gpsParser.location.isValid())
    {
        Serial.print("Latitude: ");
        Serial.println(gpsParser.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gpsParser.location.lng(), 6);
        Serial.print("Altitude: ");
        Serial.println(gpsParser.altitude.meters());
    }
    else
    {
        Serial.println("Location: Not Available");
    }

    ...
}
