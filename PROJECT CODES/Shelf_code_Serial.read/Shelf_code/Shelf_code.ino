

#include <Wire.h>



//VARIABLES
char var;
char color = 'z';

int green=0;
int red=0;

int countgreen1 = 0;
int countgreen0 = 0;
int countred1 = 0;
int countred0 = 0;


int tim1 = 0;
int tim2 = 0;
int tim3 = 0;
int tim4 = 0;

//HANDLES....................................................


//MACROS.....................................................

#define SHELF_F     13
#define SHELF_B    12
#define SHELF_EN    A5


#define RACK_R_F     8
#define RACK_R_B     9
#define RACK_R_EN    A3

#define RACK_L_F     6
#define RACK_L_B     7
#define RACK_L_EN    A5

#define RACK_DR_F     10
#define RACK_DR_B    11
#define RACK_DR_EN    A4

#define RACK_DL_F     5
#define RACK_DL_B    4
#define RACK_DL_EN    A5

#define SW1  666
#define SW2  666
#define SW3  666
#define SW4  666




#define FLOOR1_EMPTY 0
#define FLOOR1_FULL   1


//FUNCTION PROTOTYPES........................................

void SHELF_STOP(void);
void SHELF_UP(void);
void SHELF_DOWN(void);

void RACK_R_BACK(void);
void RACK_R_ON(void);
void RACK_R_OFF(void);

void RACK_L_ON(void);
void RACK_L_BACK(void);
void RACK_L_OFF(void);

void RACK_DR_BACK(void);
void RACK_DR_ON(void);
void RACK_DR_OFF(void);

void RACK_DL_ON(void);
void RACK_DL_BACK(void);
void RACK_DL_OFF(void);

void FLOOR1DOWN();
void FLOOR2DOWN();




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // disable timer compare interrupt until needed
  TIMSK1 &= ~(1 << OCIE1A);

  sei();//allow interrupts



  pinMode(RACK_R_B, OUTPUT);  // R motors forward
  pinMode(RACK_R_F, OUTPUT);  //R motors reverse


  pinMode(RACK_L_F, OUTPUT);  // down right motors forward
  pinMode(RACK_L_B, OUTPUT);  //down right motors reverse

 pinMode(RACK_DR_B, OUTPUT);  // R motors forward
  pinMode(RACK_DR_F, OUTPUT);  //R motors reverse


  pinMode(RACK_L_F, OUTPUT);  // down right motors forward
  pinMode(RACK_L_B, OUTPUT);  //down right motors reverse

  
  pinMode(SHELF_F, OUTPUT);  // SHELF upward
  pinMode(SHELF_B, OUTPUT);  //shelf downward

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);

 // color = 2;
 // green = 1;
}

void loop() {

    color = Serial.read();

  while (color != 'z')
  {
    Serial.println("out");

    if ( color == 'g' )
    {
      Serial.println("color1");
      if (green == 0)
      {
        RACK_R_ON();

        RACK_R_BACK();
        green++;
        countgreen0 = 1;

        color = 'z';
      }
      else {
        Serial.println("green=1");
        SHELF_UP();

        RACK_R_ON();

        RACK_R_BACK();

        SHELF_DOWN();
        countgreen1 = 1;
        color = 'z';
      }
    }
    else if (color == 'r' )
    {
      if (red == 0)
      {
        RACK_L_ON();

        RACK_L_BACK();
        red++;
        countred0 = 1;
        color = 'z';
      }
      else {
        SHELF_UP();

        RACK_L_ON();

        RACK_L_BACK();
        countred1 = 1;
        color = 'z';
      }


    }


  }


  /////////////////////////////////////
  if (countgreen0 == 1)
  {
    if (tim1 == 30)
    {
      Serial.println("end++");
      countgreen0 = 0;
      FLOOR1DOWN();
    }
  }
  ///////////////////////////////////////

  if ( countgreen1 == 1 )
  {

    if (tim2 == 30)
    {
      Serial.println("end++");
      countgreen1 = 0;
      FLOOR2DOWN();
    }

  }

  ////////////////////////////////////
       if(countred0==1)
      {
         if (tim3 == 30)
    {
      Serial.println("end++");
      countgreen1 = 0;
      FLOOR1DOWN();
    }
      }
  ///////////////////////////
       if (countred1==1)
      {
        if (tim4 == 30)
    {
      Serial.println("end++");
      countgreen1 = 0;
      FLOOR2DOWN();
    }
        }


}

//FUNCTION DESCRIPTION


//////////////////////////////////////////////

ISR(TIMER1_COMPA_vect)

{ //change the 0 to 1 for timer1 and 2 for timer2
  //interrupt commands here
  if ( countgreen0 == 1 )
  {
    tim1++;
    if (tim1 == 30)
    {

      TIMSK1 &= ~(1 << OCIE1A);
      TCNT1  = 0;//initialize counter value to 0
      cli(); //stop interrupts
      Serial.println("Tim1OUTTTTTTTTTTTTTTTTT ");


    }
    Serial.println("Tim1 = ");
    Serial.print(tim1);
  }


  if ( countgreen1 == 1 )
  {
    tim2++;
    if (tim2 == 30)
    {

      TIMSK1 &= ~(1 << OCIE1A);
      TCNT1  = 0;//initialize counter value to 0
      cli(); //stop interrupts
      Serial.println("Tim1OUTTTTTTTTTTTTTTTTT ");


    }
    Serial.println("Tim2 = ");
    Serial.print(tim2);
  }


if ( countred0 == 1 )
  {
    tim3++;
    if (tim3 == 30)
    {

      TIMSK1 &= ~(1 << OCIE1A);
      TCNT1  = 0;//initialize counter value to 0
      cli(); //stop interrupts
      Serial.println("Tim1OUTTTTTTTTTTTTTTTTT ");


    }
    Serial.println("Tim3 = ");
    Serial.print(tim3);
  }

  if ( countred1 == 1 )
  {
    tim4++;
    if (tim4 == 30)
    {

      TIMSK1 &= ~(1 << OCIE1A);
      TCNT1  = 0;//initialize counter value to 0
      cli(); //stop interrupts
      Serial.println("Tim1OUTTTTTTTTTTTTTTTTT ");


    }
    Serial.println("Tim4 = ");
    Serial.print(tim4);
  }
}

//////////////////////////////////////////////

void SHELF_UP()
{


  analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_F, HIGH);
  digitalWrite(SHELF_B, LOW);

  delay(7000);
  //  if(SW1==HIGH)
  // {
  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
  //  }

   delay(1000);
  Serial.println("SHELFUP");
  

}
/////////////////////////////////////////////////////////////////////////
void SHELF_DOWN()
{

  analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, HIGH);

  delay(7000);

  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
  Serial.println("SHELFDOWN");

   delay(1000);

  
}

/////////////////////////////////////////////////////////////////////////
void FLOOR1DOWN()
{

 analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, HIGH);

  delay(18500);

  //  if(SW4==HIGH)
  // {
  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
  //  }
  Serial.println("FLOOR1DOWN");
delay(3000);

RACK_DL_ON();
RACK_DL_BACK();

   analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_B, LOW);
  digitalWrite(SHELF_F, HIGH);

  delay(18500);

  //  if(SW4==HIGH)
  // {
  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
  //  }
}
/////////////////////////////////////////////////////////////////////////
void FLOOR2DOWN()
{
  Serial.println("FLOOR2DOWN");

  analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, HIGH);

  delay(10000);
  //  if(SW3==HIGH)
  // {
  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
  
  //  }

  delay(2000);
  
  RACK_DL_ON();
  RACK_DL_BACK();
  
  analogWrite (SHELF_EN, 255);

  digitalWrite(SHELF_B, LOW);
  digitalWrite(SHELF_F, HIGH);

  delay(10000);
  //  if(SW3==HIGH)
  // {
  digitalWrite(SHELF_F, LOW);
  digitalWrite(SHELF_B, LOW);
}
/////////////////////////////////////////////////////////////////////////
void RACK_R_ON()
{

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, HIGH);
  digitalWrite(RACK_R_B, LOW);

  delay(750);

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, LOW);
  digitalWrite(RACK_R_B, LOW);
  delay(750);
  Serial.println("RackOn");

}
//////////////////////////////////////////////////////
void RACK_R_BACK(void)
{

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, LOW);
  digitalWrite(RACK_R_B, HIGH);

  delay(750);

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, LOW);
  digitalWrite(RACK_R_B, LOW);

  delay(750);
  Serial.println("RackBACK");

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

}
//////////////////////////////////////////////////////
void RACK_R_OFF(void) {

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, LOW);
  digitalWrite(RACK_R_B, LOW);


}
//////////////////////////////////////////////////////
void RACK_L_ON() {

  analogWrite (RACK_L_EN, 255);

  digitalWrite(RACK_L_F, HIGH);
  digitalWrite(RACK_L_B, LOW);
  delay(800);

  analogWrite (RACK_L_EN, 255);

  digitalWrite(RACK_L_F, LOW);
  digitalWrite(RACK_L_B, LOW);

  delay(800);
  Serial.println("RackON");

}
//////////////////////////////////////////////////////
void RACK_L_BACK(void) {

  analogWrite (RACK_L_EN, 255);

  digitalWrite(RACK_L_F, LOW);
  digitalWrite(RACK_L_B, HIGH);

  delay(800);

  analogWrite (RACK_L_EN, 255);

  digitalWrite(RACK_L_F, LOW);
  digitalWrite(RACK_L_B, LOW);

  delay(800);
  Serial.println("RackBACK");
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

}
//////////////////////////////////////////////////////
void RACK_L_OFF(void) {

  analogWrite (RACK_R_EN, 255);

  digitalWrite(RACK_R_F, LOW);
  digitalWrite(RACK_R_B, LOW);


}


void RACK_DR_ON()
{

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, HIGH);
  digitalWrite(RACK_DR_B, LOW);

  delay(500);

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, LOW);
  digitalWrite(RACK_DR_B, LOW);
  delay(500);
  Serial.println("RackOn");

}
//////////////////////////////////////////////////////
void RACK_DR_BACK(void)
{

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, LOW);
  digitalWrite(RACK_DR_B, HIGH);

  delay(500);

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, LOW);
  digitalWrite(RACK_DR_B, LOW);

  delay(500);
  Serial.println("RackBACK");

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

}
//////////////////////////////////////////////////////
void RACK_DR_OFF(void) {

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, LOW);
  digitalWrite(RACK_DR_B, LOW);


}
//////////////////////////////////////////////////////
void RACK_DL_ON() {

  analogWrite (RACK_DL_EN, 255);

  digitalWrite(RACK_DL_F, HIGH);
  digitalWrite(RACK_DL_B, LOW);
  delay(100);

  analogWrite (RACK_DL_EN, 255);

  digitalWrite(RACK_DL_F, LOW);
  digitalWrite(RACK_DL_B, LOW);

  delay(100);
  Serial.println("RackBACK");

}
//////////////////////////////////////////////////////
void RACK_DL_BACK(void) {

  analogWrite (RACK_DL_EN, 255);

  digitalWrite(RACK_DL_F, LOW);
  digitalWrite(RACK_DL_B, HIGH);

  delay(100);

  analogWrite (RACK_DL_EN, 255);

  digitalWrite(RACK_DL_F, LOW);
  digitalWrite(RACK_DL_B, LOW);

  delay(100);
  Serial.println("RackBACK");
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

}
//////////////////////////////////////////////////////
void RACK_DL_OFF(void) {

  analogWrite (RACK_DR_EN, 255);

  digitalWrite(RACK_DR_F, LOW);
  digitalWrite(RACK_DR_B, LOW);


}
