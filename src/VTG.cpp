#include "Arduino.h"
#include "NMEA_Parser.h"




// https://docs.novatel.com/OEM7/Content/Logs/GPVTG.htm?Highlight=VTG
bool nmea_parser::parseVTG(const char& recChar)
{
    char *ptr;
    static nmea::VTG_fields field = nmea::VTG_fields::VTG_COG_TRUE;

    if (recChar == ',')
    {
        switch (field) 
        {
            case nmea::VTG_fields::VTG_COG_TRUE:
            {
                // Base microsecond timestamp on when first
                // field arrives
                vtg.usTimestamp = micros();

                // Set values
                vtg.cog_true = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::VTG_fields::VTG_COG_TRUE_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_COG_TRUE_IND:
            {
                // Set values
                vtg.cog_true_ind = buff[0];

                // Setup for next field
                field = nmea::VTG_fields::VTG_COG_MAG;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_COG_MAG:
            {
                // Set values
                vtg.cog_mag = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::VTG_fields::VTG_COG_MAG_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_COG_MAG_IND:
            {
                // Set values
                vtg.cog_mag_ind = buff[0];

                // Setup for next field
                field = nmea::VTG_fields::VTG_SOG_KN;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_SOG_KN:
            {
                // Set values
                vtg.sog_kn = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::VTG_fields::VTG_NAUTICAL_SPD_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_NAUTICAL_SPD_IND:
            {
                // Set values
                vtg.sog_kn_ind = buff[0];

                // Setup for next field
                field = nmea::VTG_fields::VTG_SOG_KPH;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_SOG_KPH:
            {
                // Set values
                vtg.sog_kph = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::VTG_fields::VTG_SOG_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_SOG_IND:
            {
                // Set values
                vtg.sog_kph_ind = buff[0];

                // Setup for next field
                field = nmea::VTG_fields::VTG_MODE_IND;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::VTG_fields::VTG_MODE_IND:
            {
                // This should not happen
                break;
            }

            case nmea::VTG_fields::VTG_CS:
            {
                // This should not happen
                break;
            }
        }
    }
    else if (recChar == '*')
    {
        // Set value
        vtg.mode_ind = buff[0];

        // Setup for next field
        field = nmea::VTG_fields::VTG_CS;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));
    }
    else if (recChar == '\n')
    {
        // Set value
        vtg.checksum = (int)strtol(buff, NULL, 16);

        // Update final struct
        memcpy(&vtg_final, &vtg, sizeof(vtg));

        // Reset parser
        field = nmea::VTG_fields::VTG_COG_TRUE;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;

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
