#include "NMEA_Parser.h"




nmea_parser gnssParser;
nmea::rmc_struct rmc;




void setup()
{
  Serial.begin(115200);
  Serial8.begin(115200);
  gnssParser.begin(Serial8);
}




void loop()
{
    if (gnssParser.available() && (gnssParser.getCurrMsgType() == nmea::msg_types::RMC))
    {
        rmc = gnssParser.getRMC_struct();

        Serial.print(rmc.hour);        Serial.print(",");
        Serial.print(rmc.min);         Serial.print(",");
        Serial.print(rmc.sec, 5);      Serial.print(",");
        Serial.print(rmc.pos_status);  Serial.print(",");
        Serial.print(rmc.lat_dms, 5);  Serial.print(",");
        Serial.print(rmc.lat_dms_dir); Serial.print(",");
        Serial.print(rmc.lat_dd, 5);   Serial.print(",");
        Serial.print(rmc.lon_dms, 5);  Serial.print(",");
        Serial.print(rmc.lon_dms_dir); Serial.print(",");
        Serial.print(rmc.lon_dd, 5);   Serial.print(",");
        Serial.print(rmc.sog_kn, 5);   Serial.print(",");
        Serial.print(rmc.cog_true, 5); Serial.print(",");
        Serial.print(rmc.year);        Serial.print(",");
        Serial.print(rmc.month);       Serial.print(",");
        Serial.print(rmc.day);         Serial.print(",");
        Serial.print(rmc.mag_var, 5);  Serial.print(",");
        Serial.print(rmc.mag_var_dir); Serial.print(",");
        Serial.print(rmc.mode_ind);    Serial.print(",");
        Serial.print(rmc.checksum);    Serial.print(",");
        Serial.print(rmc.usTimestamp); Serial.println();
    }
}