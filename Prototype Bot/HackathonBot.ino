#include<Servo.h>
int mtrra=5;
int mtrrb=6;
int mtrla=9;
int mtrlb=10;
int rir=12;
int lir=11;
int trig=2;
int echo=4;
int servopin=3;
int led=13;
Servo servo;
void setup() {
  servo.attach(servopin);
  servo.write(0);
  Serial.begin(9600);
  pinMode(mtrra,OUTPUT);
  pinMode(mtrrb,OUTPUT);
  pinMode(mtrla,OUTPUT);
  pinMode(mtrlb,OUTPUT);
  pinMode(rir,INPUT);
  pinMode(lir,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
 digitalWrite(mtrra,LOW);
 digitalWrite(mtrrb,LOW);
 digitalWrite(mtrla,LOW);
 digitalWrite(mtrlb,LOW);
 digitalWrite(led,HIGH);
}

void loop() {
 int l=digitalRead(lir);
 int r=digitalRead(rir);
 digitalWrite(trig,LOW);
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 long duration= pulseIn(echo,HIGH);
 int distance= (duration/2)*(0.034);
 Serial.println(distance);
 if(l==1 && r==1) {
 digitalWrite(mtrra,LOW);
 digitalWrite(mtrrb,HIGH);
 digitalWrite(mtrla,LOW);
 digitalWrite(mtrlb,HIGH);
 }
  else if(l==0 && r==0) {
 digitalWrite(mtrra,LOW);
 digitalWrite(mtrrb,LOW);
 digitalWrite(mtrla,LOW);
 digitalWrite(mtrlb,LOW);
 }
  else if(l==0 && r==1) {
 digitalWrite(mtrra,HIGH);
 digitalWrite(mtrrb,LOW);
 digitalWrite(mtrla,LOW);
 digitalWrite(mtrlb,HIGH);
 }
  else if(l==1 && r==0) {
 digitalWrite(mtrra,LOW);
 digitalWrite(mtrrb,HIGH);
 digitalWrite(mtrla,HIGH);
 digitalWrite(mtrlb,LOW);
 }
 if(distance<=10) {
 digitalWrite(mtrra,LOW);
 digitalWrite(mtrrb,LOW);
 digitalWrite(mtrla,LOW);
 digitalWrite(mtrlb,LOW);
 digitalWrite(led,LOW);
 }
 else if(distance>10) {
  digitalWrite(led,HIGH);
 }
 if( distance<=10 && l==0 && r==0) {
 servo.write(90);
 delay(1000);
 servo.write(0);
 }
}
