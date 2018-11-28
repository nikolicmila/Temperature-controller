#include <TimerOne.h>

int procent;
long int period;

const byte Led=13;
int value;
int tempPin = A0;
float setTemp = 30;
float celsius;

int kp = 5;
int ki = 10;


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
  
  value = analogRead(tempPin);
  float midvalue = ( value/1024.0)*5000; 
  celsius = midvalue/10;
    celsius = constrain (celsius, -55, 150);
  
  Serial.println(celsius); 
  Serial.println(setTemp); 
  /*Serial.println(kp); 
  Serial.println(ki); */
  
  double error = setTemp - celsius;
  Serial.println(error); 
  double errorSum = errorSum + error;
  
  if (error > 0){
    double output = kp * error + ki * errorSum; 
    procent = constrain(output,0,100);
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
