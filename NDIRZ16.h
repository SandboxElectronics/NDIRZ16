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
		NDIRZ16(Stream *myserial);

        uint16_t getppm(void);
        uint8_t gettemperature(void);

		
    private:
		Stream *_myserial;
        void sendcommand(uint8_t *pcommand);
        uint8_t getresult(uint16_t *pppm, uint8_t *ptemp);
	    uint8_t measure[9]; //=  {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
        uint8_t calibrate[9];// = {0xFF,0x87,0x87,0x00,0x00,0x00,0x00,0x00,0xF2};
};
#endif		
