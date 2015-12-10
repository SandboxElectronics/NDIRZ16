#include <Wire.h>
#include <SPI.h>
#include <SC16IS750.h>
#include <string.h>
#include <NDIRZ16.h>


SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_BB);
NDIRZ16 mySensor = NDIRZ16(&i2cuart);

void setup() 
{
    Serial.begin(115200);
    i2cuart.begin(9600);

    if (i2cuart.ping()) {
        Serial.println("SC16IS750 found.");
        Serial.println("Wait 10 seconds for sensor initialization...");
    } else {
        Serial.println("SC16IS750 not found.");
        while(1);
    }

    power(1);
    //Wait for the NDIR sensor to initialize.
    delay(10000);
};

void loop() {
    if (mySensor.measure()) {
        Serial.print("CO2 Concentration is ");
        Serial.print(mySensor.ppm);
        Serial.println("ppm");
    } else {
        Serial.println("Sensor communication error.");
    }
    delay(1000);
}

//Power control function for NDIR sensor. 1=ON, 0=OFF
void power (uint8_t state) {
    i2cuart.pinMode(0, INPUT);      //set up for the power control pin
 
    if (state) {
        i2cuart.pinMode(0, INPUT);  //turn on the power of MH-Z16
    } else {
        i2cuart.pinMode(0, OUTPUT);
        i2cuart.digitalWrite(0, 0); //turn off the power of MH-Z16
    }
}

//Zero Point (400ppm) Calibration function for NDIR sensor. Only used when necessary.
//Make sure that the sensor has been running in fresh air (~400ppm) for at least 20 minutes before calling this function.
void calibrate() {
    i2cuart.pinMode(1, OUTPUT);    //set up for the calibration pin.
     
    i2cuart.digitalWrite(1, LOW);  //start calibration of MH-Z16 under 400ppm
    delay(10000);                  //5+ seconds needed for the calibration process
    i2cuart.digitalWrite(1, HIGH); //toggle the pin HIGH back to normal operation
}
