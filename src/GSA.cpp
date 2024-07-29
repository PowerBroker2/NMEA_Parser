#include "Arduino.h"
#include "NMEA_Parser.h"




// https://docs.novatel.com/OEM7/Content/Logs/GPGSA.htm?Highlight=GSA
bool nmea_parser::parseGSA(const char& recChar)
{
    char *ptr;
    static nmea::GSA_fields field = nmea::GSA_fields::GSA_MODE_MA;

    if (recChar == ',')
    {
        switch (field) 
        {
            case nmea::GSA_fields::GSA_MODE_MA:
            {
                // Base microsecond timestamp on when first
                // field arrives
                gsa.usTimestamp = micros();

                // Set values
                gsa.mode_ma = buff[0];

                // Setup for next field
                field = nmea::GSA_fields::GSA_MODE_123;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_MODE_123:
            {
                // Set values
                gsa.mode_123 = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_1;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_1:
            {
                // Set values
                gsa.temp_prns[0] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_2;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_2:
            {
                // Set values
                gsa.temp_prns[1] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_3;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_3:
            {
                // Set values
                gsa.temp_prns[2] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_4;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_4:
            {
                // Set values
                gsa.temp_prns[3] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_5;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_5:
            {
                // Set values
                gsa.temp_prns[4] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_6;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_6:
            {
                // Set values
                gsa.temp_prns[5] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_7;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_7:
            {
                // Set values
                gsa.temp_prns[6] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_8;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_8:
            {
                // Set values
                gsa.temp_prns[7] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_9;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_9:
            {
                // Set values
                gsa.temp_prns[8] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_10;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_10:
            {
                // Set values
                gsa.temp_prns[9] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_11;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_11:
            {
                // Set values
                gsa.temp_prns[10] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PRN_12;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PRN_12:
            {
                // Set values
                gsa.temp_prns[11] = atoi(buff);

                // Setup for next field
                field = nmea::GSA_fields::GSA_PDOP;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_PDOP:
            {
                // Set values
                gsa.pdop = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GSA_fields::GSA_HDOP;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_HDOP:
            {
                // Set values
                gsa.hdop = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GSA_fields::GSA_VDOP;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_VDOP:
            {
                // Set values
                gsa.vdop = strtod(buff, &ptr);

                // Setup for next field
                field = nmea::GSA_fields::GSA_SYS_ID;

                buffIdx = 0;
                memset(buff, '\0', sizeof(buff));

                break;
            }

            case nmea::GSA_fields::GSA_SYS_ID:
            {
                // This should not happen
                break;
            }

            case nmea::GSA_fields::GSA_CS:
            {
                // This should not happen
                break;
            }
        }
    }
    else if (recChar == '*')
    {
        // Set value
        gsa.sys_id = atoi(buff);

        switch (gsa.sys_id) 
        {
            case nmea::sys_id::GPS:
            {
                memcpy(gsa.gps_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }

            case nmea::sys_id::GLONASS:
            {
                memcpy(gsa.glonass_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }

            case nmea::sys_id::GALILEO:
            {
                memcpy(gsa.galileo_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }

            case nmea::sys_id::BEIDOU:
            {
                memcpy(gsa.beidou_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }

            case nmea::sys_id::QZSS:
            {
                memcpy(gsa.qzss_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }

            case nmea::sys_id::NAVIC:
            {
                memcpy(gsa.navic_prns, gsa.temp_prns, sizeof(gsa.temp_prns));
            }
        }

        // Setup for next field
        field = nmea::GSA_fields::GSA_CS;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));
    }
    else if (recChar == '\n')
    {
        // Set value
        gsa.checksum = (int)strtol(buff, NULL, 16);

        // Reset parser
        field = nmea::GSA_fields::GSA_MODE_MA;

        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;
        
        if (calcChecksum == gsa.checksum)
        {
            // Reset checksum
            calcChecksum = 0;

            // Update final struct
            memcpy(&gsa_final, &gsa, sizeof(gsa));

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
