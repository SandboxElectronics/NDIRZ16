#include <NDIRZ16.h>
#include <SoftwareSerial.h>

//Arduino UNO Pin D2 (Software Serial Rx) <===> Adaptor's Green  Wire (Tx)
//Arduino UNO Pin D3 (Software Serial Tx) <===> Adaptor's Yellow Wire (Rx)
SoftwareSerial mySerial(2,3);
NDIRZ16 myco2sensor = NDIRZ16(&mySerial);

void setup() 
{
    Serial.begin(115200);
    mySerial.begin(9600);
    Serial.println("Wait 10 seconds for the sensor to starup");
    delay(10000);
};

void loop() {
    if (mySensor.measure()) {
        Serial.print("CO2 Concentration is ");
        Serial.print(mySensor.ppm);
        Serial.println("ppm");
    }
    delay(1000);
}
