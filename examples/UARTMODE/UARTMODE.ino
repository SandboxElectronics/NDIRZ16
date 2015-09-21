#include <Wire.h>
#include <SPI.h>
#include <SC16IS750.h>
#include <string.h>
#include <NDIRZ16.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); //pin2 rx, pin3 tx
NDIRZ16 myco2sensor = NDIRZ16(&mySerial);
//Connect TX and RX with a wire and run this sketch

void setup() 
{
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(115200);
  Serial.println("Waiting for the sensor to starup");
//  delay(15000);
  Serial.println("Connecting to the sensor");
  mySerial.begin(9600);
    
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
