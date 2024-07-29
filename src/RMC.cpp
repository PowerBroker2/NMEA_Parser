#include "Arduino.h"
#include "NMEA_Parser.h"




// https://docs.novatel.com/OEM7/Content/Logs/GPRMC.htm?Highlight=RMC
bool nmea_parser::parseRMC(const char& recChar)
{
    char *ptr;
    static nmea::RMC_fields field = nmea::RMC_fields::RMC_TIME;

    if (recChar == ',')
    {
        switch (field) 
        {
            case nmea::RMC_fields::RMC_TIME:
            {
                // Base microsecond timestamp on when first
                // field arrives
                rmc.usTimestamp = micros();

                // Set values
                double time = strtod(buff, &ptr);
                rmc.hour    = (int)(time / 10000);
                rmc.min     = (int)((time - (rmc.hour * 10000)) / 100);
                rmc.sec     = (double)(time - (rmc.hour * 10000) - (rmc.min * 100));

                // Setup for next field
                field = nmea::RMC_fields::RMC_POS_STATUS;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_POS_STATUS:
            {
                // Set value
                rmc.pos_status = buff[0];

                // Setup for next field
                field = nmea::RMC_fields::RMC_LAT;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_LAT:
            {
                // Set value
                rmc.lat_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::RMC_fields::RMC_LAT_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_LAT_DIR:
            {
                // Set value
                rmc.lat_dms_dir = buff[0];
                rmc.lat_dd      = dm_dd(rmc.lat_dms, rmc.lat_dms_dir);

                // Setup for next field
                field = nmea::RMC_fields::RMC_LON;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_LON:
            {
                // Set value
                rmc.lon_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::RMC_fields::RMC_LON_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_LON_DIR:
            {
                // Set value
                rmc.lon_dms_dir = buff[0];
                rmc.lon_dd      = dm_dd(rmc.lon_dms, rmc.lon_dms_dir);

                // Setup for next field
                field = nmea::RMC_fields::RMC_SOG_KN;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_SOG_KN:
            {
                // Set value
                rmc.sog_kn = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::RMC_fields::RMC_COG_TRUE;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_COG_TRUE:
            {
                // Set value
                rmc.cog_true = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::RMC_fields::RMC_DATE;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_DATE:
            {
                // Set value
                int date  = atoi(buff);
                rmc.day   = (int)(date / 10000);
                rmc.month = (int)((date - (rmc.day * 10000)) / 100);
                rmc.year  = (int)(2000 + date - (rmc.day * 10000) - (rmc.month * 100));

                // Setup for next field
                field = nmea::RMC_fields::RMC_MAG_VAR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_MAG_VAR:
            {
                // Set value
                rmc.mag_var = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::RMC_fields::RMC_VAR_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_VAR_DIR:
            {
                // Set value
                rmc.mag_var_dir = buff[0];

                // Setup for next field
                field = nmea::RMC_fields::RMC_MODE_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::RMC_fields::RMC_MODE_IND:
            {
                // This should not happen
                break;
            }

            case nmea::RMC_fields::RMC_CS:
            {
                // This should not happen
                break;
            }
        }
    }
    else if (recChar == '*')
    {
        // Set value
        rmc.mode_ind = buff[0];

        // Setup for next field
        field = nmea::RMC_fields::RMC_CS;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));
    }
    else if (recChar == '\n')
    {
        // Set value
        rmc.checksum = (int)strtol(buff, NULL, 16);

        // Reset parser
        field = nmea::RMC_fields::RMC_TIME;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;
        
        if (calcChecksum == rmc.checksum)
        {
            // Reset checksum
            calcChecksum = 0;

            // Update final struct
            memcpy(&rmc_final, &rmc, sizeof(rmc));

            return true;
        }

        // Reset checksum
        calcChecksum = 0;
        
        return false;
    }
    else if (isspace(recChar))
    {
        // skip
    }
    else
    {
        buff[buffIdx] = recChar;
        buffIdx++;
    }

    return false;
}
