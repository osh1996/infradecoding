#include <Arduino.h>
#include <TimerOne.h> // make sure to install this library to run!!
#include <stdio.h>
#include <CircularBuffer.h> //same with this library!
#define CIRCULAR_BUFFER_INT_SAFE

int dataPin = 3; //input from sensor
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinCprime = 7;
volatile int timer = 0;//timer in milliseconds
CircularBuffer <int, 7> buffer;
int total = 0;

void BD(CircularBuffer<int, 7> buffr);
unsigned long binaryToDecimal(char *binary, int length);

void isr() { //interrupt service routine triggered on Falling edge of signal
  noInterrupts();

  if(timer < 15 && timer > 11){
    //Serial.println("START");
  }
  else if(timer <= 1){
    buffer.unshift(0);
    //Serial.println(0);
  }
  else if(timer > 1 && timer < 4){
    buffer.unshift(1);
    //Serial.println(1);
  }
  else{
    //Serial.println("STOP");
  }
  timer = 0; //reset timer
  interrupts();
}

void callback(){
  timer++;//current time in milliseconds
}

void setup() {
  pinMode(dataPin, INPUT_PULLUP); //attach data pin
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinCprime, OUTPUT);
  Serial.begin(115200); //115k bits per second
  Timer1.initialize(1000); //init timer to trigger every one ms
  Timer1.attachInterrupt(callback);
  attachInterrupt(digitalPinToInterrupt(dataPin), isr, FALLING); //attaches interrupt to data coming from circuit
}

void loop() {
  BD(buffer);
  if(total == 162){
    Serial.println("A");
  }
  else if(total == 42){
    Serial.println("B");
  }
  else if(total == 52){
    Serial.println("C");
  }
  else if(total == 67){
    Serial.println("Cprime");
  }
  total = 0;
}

void BD(CircularBuffer<int, 7> buffr){
  total += buffr[7] * 128;
  total += buffr[6] * 64;
  total += buffr[5] * 32;
  total += buffr[4] * 16;
  total += buffr[3] * 8;
  total += buffr[2] * 4;
  total += buffr[1] * 2;
  total += buffr[0];
  buffr.pop();
}
