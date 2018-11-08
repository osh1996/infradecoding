#include <Arduino.h>
#include <TimerOne.h> // make sure to install this library to run!!

int dataPin = 3; //input from sensor
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinCprime = 7;
volatile int timer = 0;//timer in milliseconds
volatile int buff[7]; //buffer to hold 8 bits of data
volatile bool flag = 0;
volatile int x = 0;

void isr() { //interrupt service routine triggered on Falling edge of signal
noInterrupts();
if(timer <= 16 || timer >= 12){ //start bit
  flag = 1; //start filling the buffer
}
if(flag) {
  buff[x] = timer;
}
if(x == 7) {
  x = 0;
  flag = 0;//reset all values when buffer is full
  timer = 0;
}
//Serial.println(timer);
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
  //Serial.print(digitalRead(3));
  //timer++;
}

void parseBuffer(){

}

void binaryToLED(){

}
