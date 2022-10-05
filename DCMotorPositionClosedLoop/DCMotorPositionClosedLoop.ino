#include <PID_v1.h>
double PID_Setpoint, PID_Input, PID_Output;
double Kp=0.75, Ki=0.0, Kd=0;
PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, Kp, Ki, Kd, DIRECT);

//Define Pins. Constants won't change. They're used here to set pin numbers.
const int MotorPinPWM = 5; // L298N ENA
const int MotorPin1 = 6; // L298N IN1
const int MotorPin2 = 7; // L298N IN2
const int EncoderPinA = 2;   // Encoder Pin A. Interrupt 0
const int EncoderPinB = 3;  // Encoder Pin B. Interrupt 1
const int PPR = 280; // 280 pulse per revolution Encoder
//Initialize Variables
volatile int counts = 0; //counts the encoder counts. The encoder has counts/rev

void setup() {
  // put your setup code here, to run once:
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPinPWM, OUTPUT);
  //Serial setup
  Serial.begin(115200);
  //Encoder setup
  pinMode(EncoderPinA, INPUT_PULLUP); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), readEncoder, CHANGE); //attach interrupt to PIN 2

  PID_Setpoint = 360 * 280 / 360; // 360 degrees x 280ppr / 360 degrees;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 150);
}

void loop() {
  PID_Input = counts;
  myPID.Compute();
  motorOutput(PID_Output);
  Serial.print("Motor PWM = ");
  Serial.print(PID_Output);
  Serial.print(" , Encoder counts = ");
  Serial.println(counts);
  delay(1);
  
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts + 1;
  }
}

void motorOutput(int out){
  if(out>0){
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, HIGH);
    analogWrite(MotorPinPWM, abs(out));
  }
  else{
    digitalWrite(MotorPin1, HIGH);
    digitalWrite(MotorPin2, LOW);
    analogWrite(MotorPinPWM, abs(out));
  }
}
