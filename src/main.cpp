#include <Arduino.h>

int dataPin = 3;
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinCprime = 7;

void isr() { //interrupt service routine

}

void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin, INPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinCprime, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(dataPin, isr, CHANGE); //attaches interrupt to data coming from circuit
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
