/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>*/

//Define Pins. Constants won't change. They're used here to set pin numbers. Pin 20 & 21 is interrupt
const int EncoderPinA = 21;   // Encoder Pin A. Interrupt 2
const int EncoderPinB = 20;  // Encoder Pin B. Interrupt 3
//Initialize Variables
volatile int counts = 0; //counts the encoder counts. The encoder has counts/rev

void setup(){
  Serial.begin(115200);
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, HIGH); //initialize Pin States
  digitalWrite(EncoderPinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), readEncoder, CHANGE); //attach interrupt to PIN 21
}

void loop() {
  Serial.println(counts);
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts+1;
  }
}
