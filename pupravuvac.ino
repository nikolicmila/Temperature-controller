int kp;
float setTemp;
int val;
int tempPin = A0;

void setup()
{
setTemp=26;
Serial.begin(9600);
}
void loop()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;

double error = setTemp - cel;
double output = kp * error; 

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();

Serial.print("output = ");
Serial.print(output);
Serial.println();
delay(1000);
}
