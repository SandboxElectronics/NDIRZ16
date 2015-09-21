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

#include <NDIRZ16.h>

//#define _NDIR_DEBUG_ON_

NDIRZ16::NDIRZ16(Stream *myserial)
{
	    uint8_t lmeasure[9] =  {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
        uint8_t lcalibrate[9] = {0xFF,0x87,0x87,0x00,0x00,0x00,0x00,0x00,0xF2};
		uint8_t i;
	_myserial = myserial;
	for (i=0;i<9;i++) {
		measure[i]=lmeasure[i];
    }
	for (i=0;i<9;i++) {
		calibrate[i]=lcalibrate[i];
    }

}





uint16_t NDIRZ16::getppm(void)
{
    uint16_t co2ppm;
	uint8_t temperature;
	sendcommand(measure);
    getresult(&co2ppm,&temperature);
	
	return co2ppm;
}

uint8_t NDIRZ16::gettemperature(void)
{
    uint16_t co2ppm;
	uint8_t temperature;
	sendcommand(measure);
    getresult(&co2ppm,&temperature);
	
	return temperature;
}

void NDIRZ16::sendcommand(uint8_t *pcommand)
{
    uint8_t i;
 
    for (i=0;i<9;i++) {
        _myserial->write(pcommand[i]);
        
    }
    
}
uint8_t NDIRZ16::getresult(uint16_t *pppm, uint8_t *ptemp)
{
    uint8_t i;
    uint8_t buffer[10];
    
    _myserial->setTimeout(100);
    _myserial->readBytes((char*)buffer,9);
#ifdef _NDIR_DEBUG_ON_    
    Serial.println("Received data: ");
    
    for (i=0;i<9;i++) {
        Serial.print(buffer[i],HEX);
        Serial.print(" ");
        
    }
   
    Serial.println(" ");
#endif     
    if (buffer[0] != 0xff) {
#ifdef _NDIR_DEBUG_ON_   
      Serial.println("error 2");
      Serial.println(i);
      Serial.println(buffer[0]);
#endif 
      return 0;
    }
    
    if (buffer[1] != 0x86) {
#ifdef _NDIR_DEBUG_ON_  
      Serial.println("error 3");
      Serial.println(i);
      Serial.println(buffer[1]);
#endif 
      return 0;
    }
   
    *pppm = buffer[3];
    *pppm |= ((int16_t)buffer[2] << 8);
  
    *ptemp = buffer[4] -40;  
    
    
    return 1;
}
