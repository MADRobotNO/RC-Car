//Created by Martin Agnar Dahl for MAD Robot

#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK driver (2000, "", 12);

int joyX = A0;
int joyY = A1;
int but = 2;
int but2 = 5;
int valArray[4];
int ledOn = 11;

int joyValX;
int joyValY;
int butVal;
int butVal2;

void setup()
{
pinMode(joyX, INPUT);
pinMode(joyY, INPUT);
pinMode(ledOn, OUTPUT);
pinMode(but, INPUT);
pinMode(but2, INPUT);
Serial.begin(9600);  // Debugging only
if (!driver.init())
Serial.println("init failed");
digitalWrite(ledOn, HIGH);
}

void loop()
{
joyValX = analogRead(joyX);
joyValX = map (joyValX, 0, 1023, 0, 6);
joyValY = analogRead(joyY);
joyValY = map (joyValY, 0, 1023, 0, 6);
butVal = digitalRead(but);
butVal2 = digitalRead(but2);
delay(10);

valArray[0] = joyValX;
valArray[1] = joyValY;
valArray[2] = butVal;
valArray[3] = butVal2;

/* Serial.print(digitalRead(but)); //debugg
Serial.print(" ");
Serial.println(butVal2); //debugg end */

if (joyValX!=3 || joyValY!=3 || butVal!=1 || but2!=1 )
{
driver.send((uint8_t *)valArray, 8);
driver.waitPacketSent();
delay(20);
}
}
