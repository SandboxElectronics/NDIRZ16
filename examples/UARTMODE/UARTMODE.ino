#include <string.h>
#include <NDIRZ16.h>
#include <SoftwareSerial.h>

//Arduino UNO Pin D2 (Software Serial Rx) <===> Adaptor's Green  Wire (Tx)
//Arduino UNO Pin D3 (Software Serial Tx) <===> Adaptor's Yellow Wire (Rx)
SoftwareSerial mySerial(2,3);
NDIRZ16 myco2sensor = NDIRZ16(&mySerial);

void setup() 
{
  pinMode(2,INPUT);  
  pinMode(3,OUTPUT);
  Serial.begin(115200);
  Serial.println("Waiting for the sensor to starup");
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
