


#include <Wire.h>
#include <VL53L0X.h>
#include <Stepper.h>

//VARIABLES
        
boolean color;
int IRs=0;
int IRs2;
  int counter=0;
  int counter2=0;
  int frequency = 0;


//HANDLES....................................................
VL53L0X sensor;

//MACROS.....................................................

#define stepPin 2
#define dirPin 3
#define IR1 6
#define IR2 8
//Color sensor macros.........................
#define S0 9
#define S1 10
#define S2 12
#define S3 13
#define sensorOut 11
#define rf_max 261
#define rf_min 162
#define bf_max 196
#define bf_min 140
#define gf_max 209
#define gf_min 160
int rf = 0;
int bf = 0;
int gf = 0;
//FUNCTION PROTOTYPES........................................

void Conv_ON(int);
void Conv_OFF(void);
void Conv_BACK(void);
void IR1Fun();
void IR2Fun();
void distance_sen();
boolean COLOR_read(void);
const int stepsPerRevolution = 6400;
  Stepper myStepper(stepsPerRevolution,stepPin,dirPin);
  char sig='g';


  
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  Wire.begin();
  myStepper.setSpeed(350);
  //colorsensor init..................
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //sensor.setTimeout(500);
  /*if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }*/

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous(0);

    pinMode (IR1, INPUT); // sensor pin INPUT
    pinMode (IR2, INPUT); // sensor pin INPUTp gffff 34
  
  pinMode (stepPin, OUTPUT); // sensor pin INPUT
  pinMode (dirPin, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  
while(1){

 IR1Fun();
  IR2Fun();
 
 
  distance_sen();
  }
//////////////////////////////////////////////////////////////////////////////////////////

  

  
}
   




//FUNCTIONS DEFINITION
//////////////////////////////////////////////////////
 void Conv_ON(int x){
  
  
 myStepper.step(x);

     }
////////////////////////////////////////////////////// 
    void  Conv_OFF(){
        
  digitalWrite(stepPin,HIGH);
  delay(500);
  digitalWrite(stepPin,LOW);
  delay(500);
   }
//////////////////////////////////////////////////////

    void Conv_BACK(int x){
        
  myStepper.step(-x);
   }
//////////////////////////////////////////////////////


//     COLOR_read();
boolean COLOR_read(void){
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  rf = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  rf = map(rf, 20,80,255,0);
  //Serial.print("rf=");
  //Serial.print(rf);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  gf = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  gf = map(gf, 25,105,255,0);
  //Serial.print("gf=");
  //Serial.print(gf);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  bf = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  bf = map(bf, 15,75,255,0);
  //Serial.print("bf=");
  //Serial.println(bf);
  if(rf<rf_max&&rf>rf_min&&gf<gf_max&&gf>gf_min&&bf<bf_max&&bf>bf_min){
    return 1;    //red
  }
  else{
    return 0;  //green
  }
  }
//////////////////////////////////////////////////////////////// 
    void IR1Fun()
    {
         int IRs = digitalRead(IR1);
      Conv_ON(stepsPerRevolution);
  if (IRs==0){
    Serial.println("detect");
    counter++;}
  while(IRs==0){
    if (counter==1){
      Serial.println("couter==1");
    while(sig!='a'){
      sig=Serial.read();
    }
    }
    else if (counter==3){
    counter=0;
    sig='s';
    Serial.println("sig changed");
  }
  Conv_ON(stepsPerRevolution);
  IRs=digitalRead(IR1);
    }
    }
/////////////////////////////////////////////////////////////////////////
void IR2Fun()
{
    IRs2 = digitalRead(IR2);
   if (IRs2==1)
  {
    if(counter2%2==0)
    {
      Conv_ON(200);
      delay(1000);
      if (COLOR_read()==1){
        Serial.println("red");
      }
      else {
        Serial.println("green");
      }
    }
    counter2++;
  }
 
}
//////////////////////////////////////////////////////////////////////////////
void distance_sen()

{ 
  Serial.println(sensor.readRangeContinuousMillimeters());
  
   if(sensor.readRangeContinuousMillimeters()<=499)
  {
    
      while(sig!='b'){
      sig=Serial.read();}
      
       Conv_ON(5*stepsPerRevolution);
                                       //delay until suction routine end
      
  }
   if(sensor.readRangeContinuousMillimeters()<=499)
  {
    delay(4000);
      while(1)
      {
      if(color==1)
      {
         Conv_ON(5*stepsPerRevolution);
         break;
      }
      else 
      {
         Conv_BACK(5*stepsPerRevolution);
         break;
      }
    }     
  }
  
}
