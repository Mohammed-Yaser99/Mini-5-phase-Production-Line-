#include <Wire.h>

#define LED 12

#define SLAVEADDRESS 0x8

byte sendData = 0;

void setup()
{
pinMode(LED,OUTPUT);
Wire.begin(SLAVEADDRESS);
Wire.onReceive(receiveFun);

}

void loop()
{

delay(100);
}

void receiveFun (int bytes)
{
byte recvData = Wire.read();

if (recvData == 1)
{
digitalWrite(LED,HIGH);
}
else
{
digitalWrite(LED,LOW);
}
delay(500);


}
