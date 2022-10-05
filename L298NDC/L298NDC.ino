// ProStrain Technologies
// By Zharif Zubaidi
// Please contact us at info@prostrain.com.my if you have any inquiries.

#include "PID_v1.h"

//Define Pins. Constants won't change. They're used here to set pin numbers. Pin 20 & 21 is interrupt
const int EncoderPinA = 2;   // Encoder Pin A. Interrupt 0
const int EncoderPinB = 3;  // Encoder Pin B. Interrupt 1
//Initialize Variables
volatile int counts = 0; //counts the encoder counts. The encoder has counts/rev

int motor1pin1 = 5; // L298N IN3
int motor1pin2 = 6; // L298N IN4

// Configure PID
double kp = 0.5, ki = 0.05,kd = 0.01; //Modify according to needs
double input = 0, output = 0, setpoint = 0;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  //Serial setup
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  //Encoder setup
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, HIGH); //initialize Pin States
  digitalWrite(EncoderPinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), readEncoder, CHANGE); //attach interrupt to PIN 2
  //PID setup
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-255,255);
}

void loop() {
  setpoint = ((-90 * 7)/9); //Target rotation in degree. Converting to PPR by multiplying with 7/9.
  //Note that gear ratio = 20:1, 140 ppr, X2 encoder hence 280 ppr
  input = counts; //Reading from encoder in ppr 
  myPID.Compute(); //Calculate output
  motorPWM(output); //Drive motor
  Serial.println(setpoint);
  Serial.println(output);
  Serial.println(counts); //Monitor motor position
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts+1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts-1;
  }
}

void motorPWM(int out){
  if(out>0){
    moveCW(out);
  }
  else{
    moveCCW(out);
  }
}


void moveCCW(int CCW){
  CCW = CCW*-1;
  //analogWrite(motor1pin1, CCW);
  //digitalWrite(motor1pin2, LOW);
  Serial.println(CCW);
  //delay(50);
}

void moveCW(int CW){
  //CW = CW*-1;
  //digitalWrite(motor1pin1, LOW);
  //analogWrite(motor1pin2, CW);
  Serial.println(CW);
  //delay(50);
}
