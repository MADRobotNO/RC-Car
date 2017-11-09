//Created by Martin Agnar Dahl for MAD Robot

#include <RH_ASK.h> // library for RC
#include <SPI.h> // library for RC

#define trigPin A0 //echo location
#define echoPin A1 //echo location

RH_ASK driver (2000, 7); // pin for RC receiver 

int ledG = 3; // LED
int ledR = 2;

int buzz = 4; // pin for sound

int dcMot1a = 8; //motor 1
int dcMot1b = 9;
int speed1pin = 5;

int dcMot2a = 10; //motor 2
int dcMot2b = 11;
int speed2pin = 6;

long duration, distance; // variables for echo location

int w;
int m;
int a;
int x;
int y;
int but;
int but2;

void setup()
{
pinMode(speed1pin, OUTPUT);
pinMode(dcMot1a, OUTPUT);
pinMode(dcMot1b, OUTPUT);

pinMode(speed2pin, OUTPUT);
pinMode(dcMot2a, OUTPUT);
pinMode(dcMot2b, OUTPUT);

pinMode(buzz, OUTPUT);
pinMode(ledG, OUTPUT);
pinMode(ledR, OUTPUT);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 

digitalWrite(ledR, LOW);
digitalWrite(ledG, LOW);
digitalWrite(buzz, LOW);
x = 3;
y = 3;
but = 1;
but2 =1;

Serial.begin(9600); // Debugging only
if (!driver.init())
Serial.println("init failed");
}


void loop()
{

digitalWrite(ledG, HIGH);
digitalWrite(ledR, LOW);
digitalWrite(buzz, LOW);

uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t buflen = sizeof(buf);

if (driver.recv(buf, &buflen))
{
/* Serial.print("x: ");
Serial.print(buf[0]); //debug
Serial.print(" ");
Serial.print("y: ");
Serial.print(buf[2]); //debug
Serial.print(" ");
Serial.print("b1: ");
Serial.print(buf[4]); //debug
Serial.print(" ");
Serial.print("b2: ");
Serial.println(buf[6]); */ //debugg

x = buf[0];
y = buf[2];
but = buf[4];
but2 = buf[6];
}

if (y==2){ //to measure how much power motor gets
a = 100;
}
if (y==1){
a = 180;
}
if (y==0){
a = 255;
}
if (y==6){
a = 255;
}
if (y==5){
a = 180;
}
if (y==4){
a = 100;
}

analogWrite(speed1pin, a); 
analogWrite(speed2pin, a);

if (y<3 && x ==3){
forward();
}
if (y>3 && x==3){
back();
}
if (x<3 && y<3) {
leftFor();
}
if (x>3 && y<3){
fightFor();
}
if (x<3 && y==3) {
leftFor();
}
if (x>3 && y==3){
rightFor();
}
if (y==3 && x==3){
stopp();
}
if (x<3 && y>3){
leftBack();
}
if (x>3 && y>3){
rightBack();
}

if (but==0){ //if button 1 is pressed
digitalWrite(ledR, HIGH); //LED
for (int t=1; t<500; t++) //sound
{digitalWrite(buzz, HIGH);}
delay(500);
}

if (but2 == 0){ //if button 2 is pressed
check();
}
}


void forward()
{

digitalWrite(dcMot1a, HIGH);
digitalWrite(dcMot1b, LOW);
digitalWrite(dcMot2a, HIGH);
digitalWrite(dcMot2b, LOW);

}

void back()
{

digitalWrite(dcMot1a, LOW);
digitalWrite(dcMot1b, HIGH);
digitalWrite(dcMot2a, LOW);
digitalWrite(dcMot2b, HIGH);

}

void stopp()
{
digitalWrite(dcMot1a, LOW);
digitalWrite(dcMot1b, LOW);
digitalWrite(dcMot2a, LOW);
digitalWrite(dcMot2b, LOW);

}

void rightFor(){

digitalWrite(dcMot1a, LOW);
digitalWrite(dcMot1b, LOW);
digitalWrite(dcMot2a, HIGH);
digitalWrite(dcMot2b, LOW);

}

void leftFor(){

digitalWrite(dcMot1a, HIGH);
digitalWrite(dcMot1b, LOW);
digitalWrite(dcMot2a, LOW);
digitalWrite(dcMot2b, LOW);

}
void rightBack()
{

digitalWrite(dcMot1a, LOW);
digitalWrite(dcMot1b, LOW);
digitalWrite(dcMot2a, LOW);
digitalWrite(dcMot2b, HIGH);

}

void leftBack(){

digitalWrite(dcMot1a, LOW);
digitalWrite(dcMot1b, HIGH);
digitalWrite(dcMot2a, LOW);
digitalWrite(dcMot2b, LOW);

}

void check(){

digitalWrite(trigPin, LOW); // check for obstacles 
delayMicroseconds(20); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(50); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
delay(100);
if (distance < 30) // if obstacles in 30cm then turn back
{
digitalWrite(ledR, HIGH);
for (w=1; w<10; w++)
{
back();
delay(200);
}
for (m=1; m<10; m++)
{
leftBack();
delay(200);
}
}
