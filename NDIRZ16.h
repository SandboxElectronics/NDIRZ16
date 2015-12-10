/*
Description:
This is a example code for Sandbox Electronics' MH-Z16 NDIR CO2 sensor module.
You can get one of those products on
http://sandboxelectronics.com

Version:
V0.1

Release Date:
2015-01-01

Author:
Tiequan Shao          info@sandboxelectronics.com

Lisence:
CC BY-NC-SA 3.0

Please keep the above information when you use this code in your project.
*/

#ifndef _NDIRZ16_H_
#define _NDIRZ16_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class NDIRZ16 {
    public:
		NDIRZ16(Stream *stream);

        uint32_t ppm;
        uint8_t  temperature;

        uint8_t  measure();
        int32_t  getppm();
        int8_t   gettemperature();

    private:
	    static uint8_t cmd_measure[9];
		Stream *serial;

        void    sendcommand    (uint8_t *pcommand);
        uint8_t checksum_valid (uint8_t *pbuf);
};
#endif
