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

uint8_t NDIRZ16::cmd_measure[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};

NDIRZ16::NDIRZ16(Stream *stream)
{
    serial = stream;
}
/*
uint16_t NDIRZ16::getppm()
{
    uint16_t co2ppm;
	uint8_t temperature;
    measure(&co2ppm, &temperature);
	return co2ppm;
}

uint8_t NDIRZ16::gettemperature()
{
    uint16_t co2ppm;
	uint8_t temperature;
    measure(&co2ppm, &temperature);
	return temperature;
}
*/
void NDIRZ16::sendcommand (uint8_t *pcommand)
{
    uint8_t i;

    for (i=0;i<9;i++) {
        serial->write(pcommand[i]);
    }
}

uint8_t NDIRZ16::measure ()
{
    uint8_t i = 0;
    uint8_t buf[9];
    uint32_t start = millis();
    uint8_t av;

    sendcommand(cmd_measure);

    while (i < 9) {
//        Serial.println(i);
        if (av = serial->available()) {
//            Serial.print("available==");
//            Serial.println(av);
            buf[i] = serial->read();

            if (i == 0 && buf[0] != 0xFF) {
                continue;
            } else {
                i++;
            }
        }

        if (millis() - start > 1000) {
            return false;
        }

        //delay(10);
    }

//    for (i=0; i<8; i++) {
//        Serial.print(buf[i], HEX);
//        Serial.print(" ");
//    }
//
//    Serial.println(buf[8], HEX);

    if (buf[1] == 0x86) {
        if (checksum_valid(buf)) {
            ppm         = (uint16_t)buf[2] << 8 | buf[3];
            temperature = buf[4] - 40;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

uint8_t NDIRZ16::checksum_valid (uint8_t *pbuf)
{
    uint8_t i;
    uint8_t checksum = 0;

    for (i=0; i<9; i++) {
        checksum += pbuf[i];
    }

    if (checksum == 0xFF) {
        return true;
    } else {
        return false;
    }
}

int32_t NDIRZ16::getppm() {
    if (measure()) {
        return ppm;
    } else {
        return -1;
    }
}

int8_t NDIRZ16::gettemperature() {
    if (measure()) {
        return temperature;
    } else {
        return -1;
    }
}
