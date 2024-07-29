#pragma once
#include "Arduino.h"




namespace nmea
{
    enum pos_status
    {
        VALID   = 'A',
        INVALID = 'V'
    };

    enum mode_ma
    {
        AUTOMATIC = 'A',
        MANUAL    = 'M'
    };

    enum mode_123
    {
        UNAVAILABLE = 1,
        FIX_2D      = 2,
        FIX_3D      = 3
    };

    enum quality
    {
        FIX_UNAVAILABLE        = 0,
        SINGLE_POINT           = 1,
        PSEUDORANGE_DIFF       = 2,
        RTK_FIXED_AMBIGUITY    = 4,
        RTK_FLOATING_AMBIGUITY = 5,
        DEAD_RECONING          = 6,
        MANUAL_INPUT_MODE      = 7,
        SIM_MODE               = 8,
        WAAS                   = 9
    };

    enum lat_dir
    {
        NORTH = 'N',
        SOUTH = 'S'
    };

    enum lon_dir
    {
        EAST = 'E',
        WEST = 'W'
    };

    enum mode_ind
    {
        AUTONOMOUS     = 'A',
        DIFFERENTIAL   = 'D',
        ESTIMATED      = 'E',
        MANUAL_INPUT   = 'M',
        DATA_NOT_VALID = 'N'
    };

    enum sys_id
    {
        GPS     = 1,
        GLONASS = 2,
        GALILEO = 3,
        BEIDOU  = 4,
        QZSS    = 5,
        NAVIC   = 6
    };

    enum msg_types
    {
        GGA,
        GLL,
        GSA,
        RMC,
        VTG
    };

    const char GGA_header[] = "GGA";
    const char GLL_header[] = "GLL";
    const char GSA_header[] = "GSA";
    const char RMC_header[] = "RMC";
    const char VTG_header[] = "VTG";

    // https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm?Highlight=GGA
    enum GGA_fields
    {
        GGA_TIME,
        GGA_LAT,
        GGA_LAT_DIR,
        GGA_LON,
        GGA_LON_DIR,
        GGA_QUALITY,
        GGA_NUM_SV,
        GGA_HDOP,
        GGA_ALT,
        GGA_ALT_UNIT,
        GGA_UNDULATION,
        GGA_UNDULATION_UNIT,
        GGA_DIFF_AGE,
        GGA_DIFF_STATION,
        GGA_CS
    };

    struct gga_struct
    {
        int    hour;
        int    min;
        double sec;

        double lat_dms;
        char   lat_dms_dir;
        double lat_dd;

        double lon_dms;
        char   lon_dms_dir;
        double lon_dd;

        int    qual;
        int    numSats;
        double hdop;

        double alt;
        char   alt_units;
        
        double undulation;
        char   undulation_units;

        double age;
        char   station_id[4];

        int checksum;

        long usTimestamp;
    };

    // https://docs.novatel.com/OEM7/Content/Logs/GPGLL.htm?Highlight=GLL
    enum GLL_fields
    {
        GLL_LAT,
        GLL_LAT_DIR,
        GLL_LON,
        GLL_LON_DIR,
        GLL_TIME,
        GLL_STATUS,
        GLL_POS_MODE,
        GLL_CS
    };

    struct gll_struct
    {
        double lat_dms;
        char   lat_dms_dir;
        double lat_dd;

        double lon_dms;
        char   lon_dms_dir;
        double lon_dd;

        int    hour;
        int    min;
        double sec;

        char status;

        char mode_ind;

        int checksum;

        long usTimestamp;
    };
    
    // https://docs.novatel.com/OEM7/Content/Logs/GPGSA.htm?Highlight=GSA
    enum GSA_fields
    {
        GSA_MODE_MA,
        GSA_MODE_123,
        GSA_PRN_1,
        GSA_PRN_2,
        GSA_PRN_3,
        GSA_PRN_4,
        GSA_PRN_5,
        GSA_PRN_6,
        GSA_PRN_7,
        GSA_PRN_8,
        GSA_PRN_9,
        GSA_PRN_10,
        GSA_PRN_11,
        GSA_PRN_12,
        GSA_PDOP,
        GSA_HDOP,
        GSA_VDOP,
        GSA_SYS_ID,
        GSA_CS
    };

    struct gsa_struct
    {
        char mode_ma;
        int  mode_123;

        int temp_prns[12];

        int gps_prns[12];
        int glonass_prns[12];
        int galileo_prns[12];
        int beidou_prns[12];
        int qzss_prns[12];
        int navic_prns[12];

        double pdop;
        double hdop;
        double vdop;

        int sys_id;

        int checksum;

        long usTimestamp;
    };
    
    // https://docs.novatel.com/OEM7/Content/Logs/GPRMC.htm?Highlight=RMC
    enum RMC_fields
    {
        RMC_TIME,
        RMC_POS_STATUS,
        RMC_LAT,
        RMC_LAT_DIR,
        RMC_LON,
        RMC_LON_DIR,
        RMC_SOG_KN,
        RMC_COG_TRUE,
        RMC_DATE,
        RMC_MAG_VAR,
        RMC_VAR_DIR,
        RMC_MODE_IND,
        RMC_CS
    };

    struct rmc_struct
    {
        int    hour;
        int    min;
        double sec;

        char pos_status;

        double lat_dms;
        char   lat_dms_dir;
        double lat_dd;

        double lon_dms;
        char   lon_dms_dir;
        double lon_dd;

        double sog_kn;
        double cog_true;

        int year;
        int month;
        int day;

        double mag_var;
        char   mag_var_dir;

        char mode_ind;

        int checksum;

        long usTimestamp;
    };
    
    // https://docs.novatel.com/OEM7/Content/Logs/GPVTG.htm?Highlight=VTG
    enum VTG_fields
    {
        VTG_COG_TRUE,
        VTG_COG_TRUE_IND,
        VTG_COG_MAG,
        VTG_COG_MAG_IND,
        VTG_SOG_KN,
        VTG_NAUTICAL_SPD_IND,
        VTG_SOG_KPH,
        VTG_SOG_IND,
        VTG_MODE_IND,
        VTG_CS
    };

    struct vtg_struct
    {
        double cog_true;
        char   cog_true_ind;

        double cog_mag;
        char   cog_mag_ind;

        double sog_kn;
        char   sog_kn_ind;

        double sog_kph;
        char   sog_kph_ind;

        char mode_ind;

        int checksum;

        long usTimestamp;
    };
};





class nmea_parser
{
public: // <<---------------------------------------//public
    void begin(Stream& _port);

    bool available();
    bool headerIsFound() { return headerFound; };

    nmea::msg_types getCurrMsgType() { return currMsgType; };

    nmea::gga_struct getGGA_struct() { return gga_final; };
    nmea::rmc_struct getRMC_struct() { return rmc_final; };
    nmea::gsa_struct getGSA_struct() { return gsa_final; };
    nmea::vtg_struct getVTG_struct() { return vtg_final; };
    nmea::gll_struct getGLL_struct() { return gll_final; };




private: // <<---------------------------------------//private
    Stream* port;

    bool startCharFound = false;
    bool headerFound    = false;
    nmea::msg_types currMsgType;

    char buff[20];
    int  buffIdx = 0;

    // https://nmeachecksum.eqth.net/
    // The checksum is simple, just an XOR of all the bytes between
    // the $ and the * (not including the delimiters themselves),
    // and written in hexadecimal
    byte calcChecksum = 0;
    bool csFlag       = false;

    nmea::gga_struct gga;
    nmea::rmc_struct rmc;
    nmea::gsa_struct gsa;
    nmea::vtg_struct vtg;
    nmea::gll_struct gll;

    nmea::gga_struct gga_final;
    nmea::rmc_struct rmc_final;
    nmea::gsa_struct gsa_final;
    nmea::vtg_struct vtg_final;
    nmea::gll_struct gll_final;




    bool parseData(const char& recChar);
    bool parseGGA(const char& recChar);
    bool parseGLL(const char& recChar);
    bool parseGSA(const char& recChar);
    bool parseRMC(const char& recChar);
    bool parseVTG(const char& recChar);
};




double dm_dd(const double& loc, const char& dir);
