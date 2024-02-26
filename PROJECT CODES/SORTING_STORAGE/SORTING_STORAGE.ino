/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>


//VARIABLES

int Conv1_Stop_req;
int Conv1_On_req;
int LIM_SW_Shelf_Up1;
int LIM_SW_Shelf_Up2;
int LIM_SW_Shelf_Down1;
int LIM_SW_Shelf_Down2;



//HANDLES....................................................
VL53L0X sensor;

//MACROS.....................................................



#define Motor_Shelf_F 12 //forward=1
#define Motor_Shelf_B 11 //backward=2
#define Motor_Shelf_en  10
#define Motor_RackR_F  12
#define Motor_RackR_B   11
#define Motor_RackR_en 10
#define Motor_RackL_F  12
#define Motor_RackL_B   11
#define Motor_RackL_en 10

//FUNCTION PROTOTYPES........................................
    
          
void setup()
{
  Serial.begin(112500);
  Wire.begin();

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

    pinMode(Motor_Shelf_F,OUTPUT);   // R motors forward
    pinMode(Motor_Shelf_B,OUTPUT);   //R motors reverse
    pinMode(Motor_RackR_F,OUTPUT);
    pinMode(Motor_RackR_B,OUTPUT);
       pinMode(Motor_RackL_F,OUTPUT);
    pinMode(Motor_RackL_B,OUTPUT); 
}

void loop()
{
  for(;;){
  Serial.print(sensor.readRangeContinuousMillimeters());
       Serial.print(" \n");
     serial.read(); // reading color
     
       if(color=='r') {
        if(red[0]==0) {
          digitalWrite(Motor_RackR_F,HIGH);
          digitalWrite(Motor_RackR_B,HIGH);
         //ENABLE TIMER FOR RED PRODUCT 1
      
          else {
            while(
            digitalWrite(Motor_Shelf_F,HIGH);
            
          }
        }
       }
       else if(color=='g') {
        if(green[0]==0) {
          
        }
        }
       }
  if(sensor.readRangeContinuousMillimeters()>=549){
      Conv1_Stop();
      COLOR_read();   //color sensor
      Conv1_On();
    
  }
  if(sensor.readRangeContinuousMillimeters()>=499){
      Conv1_Stop();
      Suction_Down_Catch();
      Suction_Up();
      Conv1_On();
  }
  if(sensor.readRangeContinuousMillimeters()>=499){
      Conv1_Stop();
      Suction_Down_Leave();
      Suction_Up();
      Conv1_On();
  }
  
  }
 
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}


//FUNCTIONS DEFINITION
//////////////////////////////////////////////////////
 Conv1_Stop(){
  
  Serial.write(Conv1_Stop_req); //Send signal from ass arduino to STM then to conv arduino
  
 }
////////////////////////////////////////////////////// 
      Conv1_On(){
        
  Serial.write(Conv1_On_req);
  
   }
//////////////////////////////////////////////////////
Suction_Stop(){

digitalWrite(Motor_Assem_F,LOW);
        digitalWrite(MotorAssem_B,LOW);
  
}
//////////////////////////////////////////////////////
   
      Suction_Down_Catch(){
        
        digitalWrite(Motor_Assem_F,HIGH);
        digitalWrite(MotorAssem_B,LOW);
        while(1) {
        if(LIM_SW_Assem_Down==1){
          Suction_Stop();
        }
        }
        Valve_On();
        delay(500);
      }
/////////////////////////////////////////////////////////      
      Suction_Up(){

        digitalWrite(Motor_Assem_B,HIGH);
        digitalWrite(MotorAssem_F,LOW);
      }
///////////////////////////////////////////////////////////
      Suction_Down_Leave(){

         digitalWrite(Motor_Assem_F,LOW);
        digitalWrite(MotorAssem_B,HIGH);
        while(1)
        {
        if(LIM_SW_Assem_Up==1){
          Suction_Stop();
        }
        }
        
        Valve_Off();
        delay(500);
      }
////////////////////////////////////////////////////////////////      
      COLOR_read();
//////////////////////////////////////////////////////////////// 
    
