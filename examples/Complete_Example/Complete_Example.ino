#include "NMEA_Parser.h"




nmea_parser gnssParser;
nmea::gga_struct gga;
nmea::rmc_struct rmc;
nmea::gll_struct gll;
nmea::gsa_struct gsa;
nmea::vtg_struct vtg;




void setup()
{
  Serial.begin(115200);
  Serial8.begin(115200);
  gnssParser.begin(Serial8);
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
                gga = gnssParser.getGGA_struct();

                Serial.print(gga.hour);             Serial.print(",");
                Serial.print(gga.min);              Serial.print(",");
                Serial.print(gga.sec, 5);           Serial.print(",");
                Serial.print(gga.lat_dms, 5);       Serial.print(",");
                Serial.print(gga.lat_dms_dir);      Serial.print(",");
                Serial.print(gga.lat_dd, 5);        Serial.print(",");
                Serial.print(gga.lon_dms, 5);       Serial.print(",");
                Serial.print(gga.lon_dms_dir);      Serial.print(",");
                Serial.print(gga.lon_dd, 5);        Serial.print(",");
                Serial.print(gga.qual);             Serial.print(",");
                Serial.print(gga.numSats);          Serial.print(",");
                Serial.print(gga.hdop, 5);          Serial.print(",");
                Serial.print(gga.alt, 5);           Serial.print(",");
                Serial.print(gga.alt_units);        Serial.print(",");
                Serial.print(gga.undulation, 5);    Serial.print(",");
                Serial.print(gga.undulation_units); Serial.print(",");
                Serial.print(gga.age, 5);           Serial.print(",");
                Serial.print(gga.station_id);       Serial.print(",");
                Serial.print(gga.checksum);         Serial.print(",");
                Serial.print(gga.usTimestamp);      Serial.println();

                break;
            }
            
            case nmea::msg_types::RMC:
            {
                Serial.println("RMC Found");
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

                break;
            }
            
            case nmea::msg_types::GLL:
            {
                Serial.println("GLL Found");
                gll = gnssParser.getGLL_struct();

                Serial.print(gll.lat_dms, 5);  Serial.print(",");
                Serial.print(gll.lat_dms_dir); Serial.print(",");
                Serial.print(gll.lat_dd, 5);   Serial.print(",");
                Serial.print(gll.lon_dms, 5);  Serial.print(",");
                Serial.print(gll.lon_dms_dir); Serial.print(",");
                Serial.print(gll.lon_dd, 5);   Serial.print(",");
                Serial.print(gll.hour);        Serial.print(",");
                Serial.print(gll.min);         Serial.print(",");
                Serial.print(gll.sec, 5);      Serial.print(",");
                Serial.print(gll.status);      Serial.print(",");
                Serial.print(gll.mode_ind);    Serial.print(",");
                Serial.print(gll.checksum);    Serial.print(",");
                Serial.print(gll.usTimestamp); Serial.println();

                break;
            }
            
            case nmea::msg_types::GSA:
            {
                Serial.println("GSA Found");
                gsa = gnssParser.getGSA_struct();

                Serial.print(gsa.mode_ma);  Serial.print(",");
                Serial.print(gsa.mode_123); Serial.print(",");

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.temp_prns[i]); Serial.print(",");
                }

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.glonass_prns[i]); Serial.print(",");
                }

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.galileo_prns[i]); Serial.print(",");
                }

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.beidou_prns[i]); Serial.print(",");
                }

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.qzss_prns[i]); Serial.print(",");
                }

                for (int i=0; i<12; i++)
                {
                    Serial.print(gsa.navic_prns[i]); Serial.print(",");
                }

                Serial.print(gsa.pdop, 5);     Serial.print(",");
                Serial.print(gsa.hdop, 5);     Serial.print(",");
                Serial.print(gsa.vdop, 5);     Serial.print(",");
                Serial.print(gsa.checksum);    Serial.print(",");
                Serial.print(gsa.usTimestamp); Serial.println();

                break;
            }
            
            case nmea::msg_types::VTG:
            {
                Serial.println("VTG Found");
                vtg = gnssParser.getVTG_struct();

                Serial.print(vtg.cog_true, 5);  Serial.print(",");
                Serial.print(vtg.cog_true_ind); Serial.print(",");
                Serial.print(vtg.cog_mag, 5);   Serial.print(",");
                Serial.print(vtg.cog_mag_ind);  Serial.print(",");
                Serial.print(vtg.sog_kn, 5);    Serial.print(",");
                Serial.print(vtg.sog_kn_ind);   Serial.print(",");
                Serial.print(vtg.sog_kph, 5);   Serial.print(",");
                Serial.print(vtg.sog_kph_ind);  Serial.print(",");
                Serial.print(vtg.mode_ind);     Serial.print(",");
                Serial.print(vtg.checksum);     Serial.print(",");
                Serial.print(vtg.usTimestamp);  Serial.println();

                break;
            }
        }
    }
}
