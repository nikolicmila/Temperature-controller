#include <TimerOne.h>

int procent;
long int period;
const byte Led=13;

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

}
