#include <Wire.h>
#include <SPI.h>
#include <SC16IS750.h>
#include <string.h>
#include <NDIRZ16.h>


SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_BB);
NDIRZ16 myco2sensor = NDIRZ16(&i2cuart);
//Connect TX and RX with a wire and run this sketch

void setup() 
{
    Serial.begin(9600);
    i2cuart.begin(9600); 
    // UART to Serial Bridge Initialization
                 //baudrate setting
    if (i2cuart.ping()!=1) {
        Serial.println("device not found");
        while(1);
    } else {
        Serial.println("device found");
    }
    
};

void loop() 
{
    Serial.print("CO2 Concentration is ");
    Serial.print(myco2sensor.getppm());
    Serial.println("ppm");
    Serial.print("Ambient Temperature is ");
    Serial.print(myco2sensor.gettemperature());
    Serial.println("C");   
    delay(1000);	
  
  

  
};
