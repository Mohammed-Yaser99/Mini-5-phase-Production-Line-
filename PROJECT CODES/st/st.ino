#define stepPin 13
#define dirPin 12




  
void setup() {
  // put your setup code here, to run once:
  pinMode (stepPin, OUTPUT); // sensor pin INPUT
  pinMode (dirPin, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(dirPin, HIGH);

for(;;){
 
    digitalWrite(stepPin, HIGH);
  delay(500);
}
}
