#include "Arduino.h"
#include "NMEA_Parser.h"




// https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm?Highlight=GGA
bool nmea_parser::parseGGA(const char& recChar)
{
    char *ptr;
    static nmea::GGA_fields field = nmea::GGA_fields::GGA_TIME;

    if (recChar == ',')
    {
        switch (field) 
        {
            case nmea::GGA_fields::GGA_TIME:
            {
                // Base microsecond timestamp on when first
                // field arrives
                gga.usTimestamp = micros();

                // Set values
                double time = strtod(buff, &ptr);
                gga.hour    = (int)(time / 10000);
                gga.min     = (int)((time - (gga.hour * 10000)) / 100);
                gga.sec     = (double)(time - (gga.hour * 10000) - (gga.min * 100));

                // Setup for next field
                field = nmea::GGA_fields::GGA_LAT;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_LAT:
            {
                // Set value
                gga.lat_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_LAT_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_LAT_DIR:
            {
                // Set value
                gga.lat_dms_dir = buff[0];
                gga.lat_dd      = dm_dd(gga.lat_dms, gga.lat_dms_dir);

                // Setup for next field
                field = nmea::GGA_fields::GGA_LON;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_LON:
            {
                // Set value
                gga.lon_dms = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_LON_DIR;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_LON_DIR:
            {
                // Set value
                gga.lon_dms_dir = buff[0];
                gga.lon_dd      = dm_dd(gga.lon_dms, gga.lon_dms_dir);

                // Setup for next field
                field = nmea::GGA_fields::GGA_QUALITY;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_QUALITY:
            {
                // Set value
                gga.qual = atoi(buff);

                // Setup for next field
                field = nmea::GGA_fields::GGA_NUM_SV;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_NUM_SV:
            {
                // Set value
                gga.numSats = atoi(buff);

                // Setup for next field
                field = nmea::GGA_fields::GGA_HDOP;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_HDOP:
            {
                // Set value
                gga.hdop = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_ALT;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_ALT:
            {
                // Set value
                gga.alt = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_ALT_UNIT;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_ALT_UNIT:
            {
                // Set value
                gga.alt_units = buff[0];

                // Setup for next field
                field = nmea::GGA_fields::GGA_UNDULATION;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_UNDULATION:
            {
                // Set value
                gga.undulation = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_UNDULATION_UNIT;
                
                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_UNDULATION_UNIT:
            {
                // Set value
                gga.undulation_units = buff[0];

                // Setup for next field
                field = nmea::GGA_fields::GGA_DIFF_AGE;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_DIFF_AGE:
            {
                // Set value
                gga.age = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GGA_fields::GGA_DIFF_STATION;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GGA_fields::GGA_DIFF_STATION:
            {
                // This should not happen
                break;
            }

            case nmea::GGA_fields::GGA_CS:
            {
                // This should not happen
                break;
            }
        }
    }
    else if (recChar == '*')
    {
        // Set value
        strlcpy(gga.station_id, buff, sizeof(gga.station_id));

        // Setup for next field
        field = nmea::GGA_fields::GGA_CS;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));
    }
    else if (recChar == '\n')
    {
        // Set value
        gga.checksum = (int)strtol(buff, NULL, 16);

        // Reset parser
        field = nmea::GGA_fields::GGA_TIME;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;

        if (calcChecksum == gga.checksum)
        {
            // Reset checksum
            calcChecksum = 0;

            // Update final struct
            memcpy(&gga_final, &gga, sizeof(gga));

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
