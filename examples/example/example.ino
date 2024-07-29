#include "NMEA_Parser.h"




nmea_parser gnssParser;




void setup()
{
  Serial.begin(115200);
  gnssParser.begin(Serial);
}




void loop()
{
    if (gnssParser.available())
    {
        switch (gnssParser.getCurrMsgType()) 
        {
            case nmea::msg_types::GGA:
            {
                Serial.println("GGA Found");
                break;
            }
            
            case nmea::msg_types::RMC:
            {
                Serial.println("RMC Found");
                break;
            }
            
            case nmea::msg_types::GLL:
            {
                Serial.println("GLL Found");
                break;
            }
            
            case nmea::msg_types::GSA:
            {
                Serial.println("GSA Found");
                break;
            }
            
            case nmea::msg_types::VTG:
            {
                Serial.println("VTG Found");
                break;
            }
        }
    }
}
