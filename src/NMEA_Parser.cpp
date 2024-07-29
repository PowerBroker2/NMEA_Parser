#include "Arduino.h"
#include "NMEA_Parser.h"




void nmea_parser::begin(Stream& _port)
{
    port = &_port;
}




bool nmea_parser::available()
{
    while (port->available())
    {
        bool endProcessing = parseData(port->read());

        if (endProcessing)
            return true;
    }

    return false;
}




bool nmea_parser::parseData(const char& recChar)
{
    // Serial.write(recChar);

    if (recChar == '$')
    {
        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        headerFound    = false;
        startCharFound = true;
        buff[buffIdx]  = recChar;

        calcChecksum = 0;
        csFlag       = true;
    }
    else if (recChar == '*')
    {
        csFlag = false;
    }
    else if (!headerFound && (recChar != ','))
    {
        buff[buffIdx] = recChar;
        buffIdx++;
    }

    if (csFlag && !(recChar == '$'))
        calcChecksum ^= recChar;

    if (startCharFound && (!headerFound) && (recChar == ','))
    {
        if (strstr(buff, nmea::GGA_header) != NULL)
        {
            currMsgType = nmea::msg_types::GGA;
            headerFound = true;
        }
        else if (strstr(buff, nmea::GLL_header) != NULL)
        {
            currMsgType = nmea::msg_types::GLL;
            headerFound = true;
        }
        else if (strstr(buff, nmea::GSA_header) != NULL)
        {
            currMsgType = nmea::msg_types::GSA;
            headerFound = true;
        }
        else if (strstr(buff, nmea::RMC_header) != NULL)
        {
            currMsgType = nmea::msg_types::RMC;
            headerFound = true;
        }
        else if (strstr(buff, nmea::VTG_header) != NULL)
        {
            currMsgType = nmea::msg_types::VTG;
            headerFound = true;
        }
        else
        {
            // Couldn't find supported NMEA header - reset parser
            headerFound    = false;
            startCharFound = false;
        }

        // Reset buff
        buffIdx = 0;
        memset(buff, '\0', sizeof(buff));

        if (headerFound)
            return false;
    }

    if (headerFound)
    {
        switch (currMsgType) 
        {
            case nmea::msg_types::GGA:
            {
                return parseGGA(recChar);
                break;
            }

            case nmea::GLL:
            {
                return parseGLL(recChar);
                break;
            }

            case nmea::GSA:
            {
                return parseGSA(recChar);
                break;
            }

            case nmea::RMC:
            {
                return parseRMC(recChar);
                break;
            }

            case nmea::VTG:
            {
                return parseVTG(recChar);
                break;
            }
            
            default:
            {
                break;
            }
        }
    }

    return false;
}




double dm_dd(const double& loc, const char& dir)
{
	double result = (int)(loc / 100);

	result += (loc - (result * 100)) / 60.0;

	if (dir == 's' || dir == 'S' || dir == 'w' || dir == 'W')
		result = -result;

	return result;
}
