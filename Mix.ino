#include <TimerOne.h>

int procent;
long int period;
const byte Led=13;

int val;
int tempPin = A0;

int kp = 2 ;
float setTemp;
int val;
int tempPin = A0;

void setup(){
  pinMode(Led, OUTPUT);
  Serial.begin(9600);
  

  Timer1.attachInterrupt( timerIsr );
  period = 500 * 1000L;
  procent = 50;
}

void loop()
{
  Serial.print("period: ");
  Serial.print(period);
  Serial.print(" procent: ");
  Serial.println(procent);
  
  if(Serial.available()){
    switch(Serial.read()) {
      
      case 'c' : 
      period=Serial.parseInt();
      break;
      
      case 'p' :
      procent=Serial.parseInt();
      break;
    }
  }
  delay(500);
}

void timerIsr(){
  
  if(digitalRead(13) == LOW){
    Timer1.initialize(period/100*procent);
    digitalWrite( 13, HIGH);
  }
  
  else {
     Timer1.initialize(period-(period/100*procent));
     digitalWrite(13,LOW);
  }

  float cel = constrain (cel, -55, 150);

val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
cel = mv/10;

double error = setTemp - cel;
double output = kp * error; 
if (error > 0){
  procent=procent+error;
  delay(1000);
}
}
