#include "Arduino.h"
#include "NMEA_Parser.h"




// https://docs.novatel.com/OEM7/Content/Logs/GPGLL.htm?Highlight=GLL
bool nmea_parser::parseGLL(const char& recChar)
{
    char *ptr;
    static nmea::GLL_fields field = nmea::GLL_fields::GLL_LAT;

    if (recChar == ',')
    {
        switch (field) 
        {
            case nmea::GLL_fields::GLL_LAT:
            {
                // Base microsecond timestamp on when first
                // field arrives
                gll.usTimestamp = micros();

                // Set values
                gll.lat_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GLL_fields::GLL_LAT_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }
            
            case nmea::GLL_fields::GLL_LAT_DIR:
            {
                // Set values
                gll.lat_dms_dir = buff[0];
                gll.lat_dd      = dm_dd(gll.lat_dms, gll.lat_dms_dir);

                // Setup for next field
                field = nmea::GLL_fields::GLL_LON;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }
            
            case nmea::GLL_fields::GLL_LON:
            {
                // Set values
                gll.lon_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GLL_fields::GLL_LON_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }
            
            case nmea::GLL_fields::GLL_LON_DIR:
            {
                // Set values
                gll.lon_dms_dir = buff[0];
                gll.lon_dd      = dm_dd(gll.lon_dms, gll.lon_dms_dir);

                // Setup for next field
                field = nmea::GLL_fields::GLL_TIME;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }
            
            case nmea::GLL_fields::GLL_TIME:
            {
                // Set values
                double time = strtod(buff, &ptr);
                gll.hour    = (int)(time / 10000);
                gll.min     = (int)((time - (gll.hour * 10000)) / 100);
                gll.sec     = (double)(time - (gll.hour * 10000) - (gll.min * 100));

                // Setup for next field
                field = nmea::GLL_fields::GLL_STATUS;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }
            
            case nmea::GLL_fields::GLL_STATUS:
            {
                // Set values
                gll.status = buff[0];

                // Setup for next field
                field = nmea::GLL_fields::GLL_POS_MODE;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GLL_fields::GLL_POS_MODE:
            {
                // This should not happen
                break;
            }

            case nmea::GLL_fields::GLL_CS:
            {
                // This should not happen
                break;
            }
        }
    }
    else if (recChar == '*')
    {
        // Set value
        gll.mode_ind = buff[0];

        // Setup for next field
        field = nmea::GLL_fields::GLL_CS;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));
    }
    else if (recChar == '\n')
    {
        // Set value
        gll.checksum = (int)strtol(buff, NULL, 16);

        // Reset parser
        field = nmea::GLL_fields::GLL_LAT;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;
        
        if (calcChecksum == gll.checksum)
        {
            // Reset checksum
            calcChecksum = 0;

            // Update final struct
            memcpy(&gll_final, &gll, sizeof(gll));

            return true;
        }

        // Reset checksum
        calcChecksum = 0;

        return true;
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
