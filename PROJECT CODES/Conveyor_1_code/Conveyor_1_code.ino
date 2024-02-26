/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>


//VARIABLES
       int IR1status=0;
       int IR2status=0;    
       boolean color;



//HANDLES....................................................
VL53L0X sensor;

//MACROS.....................................................

#define IR1  8; 
#define  IR2 9; 

#define dirPin    2 //stepper CW or CCW
#define stepPin  3
#define red 1
#define green 0
//FUNCTION PROTOTYPES........................................

void Conv_ON(void);
void Conv_OFF(void);
void Conv_BACK(void);
boolean COLOR_read(void);


  


  
 
void setup()
{
  Serial.begin(112500);
  Wire.begin(2);

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

    pinMode (IR1, INPUT); // sensor pin INPUT
    pinMode (IR2, INPUT); // sensor pin INPUT
  
  pinMode (stepPin, OUTPUT); // sensor pin INPUT
  pinMode (dirPin, OUTPUT); 


 
}

void loop()
{


  //////////////////////////////////////////////////////////////////////First stage//////////////////////////////////////////////////////////////////
  
 for(;;)
 {
 IR1status = digitalRead (IR1);
if(IR1satus==1)
{
  Conv_OFF();
  
  Wire.beginTransmission(1); // SEND I2C TO STM
  Wire.write('a');
  Wire.endTransmission();
  
  break;
}

 }
for(;;)
{
  while(1<Wire.available())
  {
   char c = Wire.read();
  if(c == 'A')break;
  }
}

//////////////////////////////////////////////////////////////////////Second stage//////////////////////////////////////////////////////////////////

for(;;)
{
  //recieve from stm may be implemented by interrupt recieve i2c if it only makes the conveyor on
 if ( c == 'A') 
 {
  Conv_ON();
  break;
 }
 
}

//////////////////////////////////////////////////////////////////////Third stage//////////////////////////////////////////////////////////////////

 for(;;)
 {
 IR2status = digitalRead (IR2);
if(IR2satus==1)
{
  Conv_OFF();
  
// boolean color = COLOR_read(); //boolean function
  
    Conv_ON();

 break;
}

 }
 //////////////////////////////////////////////////////////////////////Fourth stage//////////////////////////////////////////////////////////////////

 
 for(;;)
 {
  Serial.print(sensor.readRangeContinuousMillimeters());
       Serial.print(" \n");
       
 
  if(sensor.readRangeContinuousMillimeters()>=499){
      Conv_OFF();
      
       Wire.beginTransmission(1); // SEND I2C TO STM
       Wire.write('b');  //Suction_Down_Catch & UP
       Wire.endTransmission(); 
      
      delay(60000); //delay until suction routine end
      Conv_ON();
  }
  
  if(sensor.readRangeContinuousMillimeters()>=499){
      Conv_OFF();
        Wire.beginTransmission(1); // SEND I2C TO STM
       Wire.write('c');  //Suction_Down_Leave & UP
       Wire.endTransmission();  
       
     delay(6000); //delay until suction routine end
      
      if(color==green)
      {
        Conv_ON();
        delay(5000);
        Conv_OFF();
         Wire.beginTransmission(1); // SEND I2C TO STM
       Wire.write('d');  //Suction_Down_Leave & UP
       Wire.endTransmission(); 
      }
      else
      {
        Conv_BACK();
        delay(5000);
        Conv_OFF();
         Wire.beginTransmission(1); // SEND I2C TO STM
       Wire.write('e');  //Suction_Down_Leave & UP
       Wire.endTransmission(); 
      }
       break;
  }
  
  }




 //////////////////////////////////////////////////////////////////////Fifth stage//////////////////////////////////////////////////////////////////



    
 

  
 }

//FUNCTIONS DEFINITION
//////////////////////////////////////////////////////
 Conv_OFF(){
  
  
 digitalWrite(dirPin, HIGH);
 
  
    digitalWrite(stepPin, HIGH);

     }
////////////////////////////////////////////////////// 
      Conv_ON(){
        
  digitalWrite(dirPin, HIGH);

    digitalWrite(stepPin, LOW);

   }
//////////////////////////////////////////////////////

    Conv_BACK(){
        
  digitalWrite(dirPin, LOW);

    digitalWrite(stepPin, HIGH);

   }
//////////////////////////////////////////////////////


//     COLOR_read();
//////////////////////////////////////////////////////////////// 
    
