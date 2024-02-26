int sol = 6;      //Tell the Arduino that the positive end of the solenoid is
                        //plugged into pin 8


int sen = 1;     //Tell the Arduino that the positive end of the Sensor is
                        //plugged into pin 1


void setup() {                   //this is included in every code we will be 
                                           //dealing with. This part runs once. 


pinMode(sol, OUTPUT); //These two lines tell the Arduino if the 
pinMode(sen, INPUT);    // connections are INPUTS or OUTPUTS
}

void loop() {         // this will run continuously after the  Void setup has
                               // run once
 digitalWrite(sol, HIGH);         // if it is high we will send power
                                                     // to the solenoid
   delay(2000);
   digitalWrite(sol, LOW);
     delay(2000);

}
