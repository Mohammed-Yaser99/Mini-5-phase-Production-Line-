/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <Stepper.h>

VL53L0X sensor;

#define stepPin 2
#define dirPin 3

const int stepperrev=6400;

Stepper myStepper(stepperrev,stepPin,dirPin);

/////////////////////////////////////////////////////////

void Conv_ON(void);
void Conv_OFF(void);

//////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Wire.begin();
 myStepper.setSpeed(350);
 
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous(0);
}

void loop()
{
 delay(500); 
  Serial.print(sensor.readRangeContinuousMillimeters());
   Serial.print(" \n");
   Conv_ON();
   
 /* if(200 < sensor.readRangeContinuousMillimeters( )< 205)
  {
      Serial.print("in");
     Conv_OFF();
     delay(5000);
  }*/
      
 
 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Conv_ON(void){
  
  Serial.println("step");
Mystepper.step(200);

     }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      void  Conv_OFF(){
        
  digitalWrite(stepPin,LOW);
  delay(500);
  digitalWrite(stepPin,LOW);
  delay(500);
   }
