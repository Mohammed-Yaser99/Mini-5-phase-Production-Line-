/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>


//VARIABLES
   char var;
   
//HANDLES....................................................


//MACROS.....................................................

#define dirPin   ;  //stepper CW or CCW
#define stepPin   ; 
#define piston_valve    ;



//FUNCTION PROTOTYPES........................................

 void PISTON_OFF(void);
 void PISTON_UP(void);
 void PISTON_DOWN(void);
 void SUCTION_OFF(void);
 void SUCTION_ON(void);



  
 
void setup()
{
  Serial.begin(112500);
  Wire.begin(3);  //THE ADDRESS OF THE ARDUNO OF THE ASSEMBLY MODULE

  Wire.onReceive(receiveEvent); // register event
  pinMode (stepPin,OUTPUT); // sensor pin INPUT
  pinMode (dirPin, OUTPUT); 
  pinMode(piston_valve, OUTPUT); 
  
 
}

void loop()
 {
    delay(100);
 }



void receiveEvent(char var)
{
    char var = Wire.read(); // receive byte as a character
    Serial.print(var);         // print the character

    switch(var)
    {
      case 'A':   PISTON_DOWN(); //suction down & catch & up
                  SUCTION_ON();
                  PISTON_UP();
                  Wire.beginTransmission(1); // SEND I2C TO STM
                   Wire.write('f');
                   Wire.endTransmission();
                  break;
                  
      case 'B':   PISTON_DOWN(); //suction down & catch & up
                  SUCTION_OFF();
                  PISTON_UP();
                  delay(500);
                   Wire.beginTransmission(1); // SEND I2C TO STM
                   Wire.write('g');
                   Wire.endTransmission();
                  break;
                  
    
    }
  }

     
////////////////////////////////////////////////////// 
  void    PISTON_UP(){
        
  digitalWrite(dirPin, HIGH);

    digitalWrite(stepPin, HIGH);

   }
//////////////////////////////////////////////////////

   void PISTON_DOWN(){
        
  digitalWrite(dirPin, LOW);

    digitalWrite(stepPin, HIGH);

   }
//////////////////////////////////////////////////////
 void PISTON_OFF(){
        
  digitalWrite(dirPin, LOW);

    digitalWrite(stepPin, LOW);

   }
//////////////////////////////////////////////////////

 void SUCTION_ON(){
        
  digitalWrite(piston_valve, HIGH);         // if it is high we will send power to the solenoid
                                                     

   }
//////////////////////////////////////////////////////
 void SUCTION_OFF(void){
        
 digitalWrite(piston_valve, LOW);         // if it is low we will cut power to the solenoid

   }


//////////////////////////////////////////////////////
