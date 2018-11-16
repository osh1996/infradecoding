#include <Arduino.h>
#include <TimerOne.h> // make sure to install this library to run!!
#include <stdio.h>

int dataPin = 3; //input from sensor
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinCprime = 7;
volatile int timer = 0;//timer in milliseconds
volatile int buff[7]; //buffer to hold 8 bits of data
volatile bool flag = 0;
volatile int x = 0;
char bin[7];


void parseBuffer();
void binaryToDecimal(char *binary, int length);

void isr() { //interrupt service routine triggered on Falling edge of signal
noInterrupts();
if(timer <= 16 || timer >= 12){ //start bit
  flag = 1; //start filling the buffer
}
else{
if(flag) {
  buff[x] = timer;
}
if(x == 7) {
  x = 0;
  Serial.println("got here!");
  parseBuffer();
  flag = 0;//reset all values when buffer is full
  timer = 0;
}
}
//Serial.println(timer);
interrupts();
digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinCprime, LOW);
digitalWrite(pinC, LOW);
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
noInterrupts();
for(x;x<7;x++){
  if(buff[x] <= 1){
    bin[x] = 0;
  }
  else{
    bin[x] = 1;
  }
}
binaryToDecimal(bin, 8);
interrupts();
}

void binaryToDecimal(char *binary, int length) {
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
    //char led;
    if (decimal == 162){
      //led = "A";
      Serial.println("A");
      digitalWrite(pinA, HIGH);
    }
    else if(decimal == 42){
      //led = "B";
            Serial.println("B");
      digitalWrite(pinB, HIGH);
    }
    else if(decimal == 52){
      //led = "Cprime";
      Serial.println("Cprime");
      digitalWrite(pinCprime, HIGH);
    }
    else{
      //led = "C";
      Serial.println("C");
      digitalWrite(pinC, HIGH);
    }
}
