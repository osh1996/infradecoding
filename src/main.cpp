#include <Arduino.h>
#include <TimerOne.h> // make sure to install this library to run!!
#include <stdio.h>

int dataPin = 3; //input from sensor
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinCprime = 7;
volatile int timer = 0;//timer in milliseconds
volatile char buff[8]; //buffer to hold 8 bits of data
volatile int x = 0; //buffer placeholder

unsigned long binaryToDecimal(char *binary, int length);

void isr() { //interrupt service routine triggered on Falling edge of signal
noInterrupts();
if(timer < 15 && timer > 11){
  Serial.println("START");
}
else if(timer <= 1){
  //buff[x] = "0";
  Serial.println(0);
  //x++;
}
else if(timer > 1 && timer < 4){
  //buff[x] = "1";
  Serial.println(1);
  //x++;
}
else{
  Serial.println("STOP");
  //Serial.println(binaryToDecimal(buff, 8));
  //x = 0; //reset buffer position
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

void loop() {}

unsigned long binaryToDecimal(char *binary, int length) {
    int i;
    unsigned long decimal = 0;
    unsigned long weight = 1;
    binary += length - 1;
    weight = 1;
    for(i = 0; i < length; ++i, --binary)
    {
        if(*binary == "1")
            decimal += weight;
        weight *= 2;
    }
    return decimal;
}
