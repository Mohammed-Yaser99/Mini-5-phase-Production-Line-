#include <Wire.h>


#define BUTTONPIN PA0
#define SLAVEADDRESS 0x8

int sendData = 0;
int buttonValue;
int b=0;
void setup()
{
pinMode(BUTTONPIN, INPUT);

Wire.begin();
}

void loop()
{

buttonValue=1;
if(buttonValue == HIGH)
{
sendData = 1;
}

else
{
sendData = 0;
}

Wire.beginTransmission(SLAVEADDRESS);
Wire.write(sendData);
delay(1000);
Wire.endTransmission();
Wire.beginTransmission(SLAVEADDRESS);
Wire.write(b);
delay(1000);
Wire.endTransmission();
delay(500);



}
