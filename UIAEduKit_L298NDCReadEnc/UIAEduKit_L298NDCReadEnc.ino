//Define Pins. Constants won't change. They're used here to set pin numbers. Pin 20 & 21 is interrupt
const int EncoderPinA = 2;   // Encoder Pin A. Interrupt 0
const int EncoderPinB = 3;  // Encoder Pin B. Interrupt 1
//Initialize Variables
volatile int counts = 0; //counts the encoder counts. The encoder has counts/rev

int motor1pin1 = 5; // L298N IN3
int motor1pin2 = 6; // L298N IN4

int speedInput = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  //Serial setup
  Serial.begin(115200);
  //Encoder setup
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, HIGH); //initialize Pin States
  digitalWrite(EncoderPinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), readEncoder, CHANGE); //attach interrupt to PIN 2
}

void loop() {
  // put your main code here, to run repeatedly:   
  speedInput = 100; //Enter speed here 100 - 255 only. Positive CW. Negative CCW.
  motorPWM(speedInput); //Drive motor
  Serial.println(counts); //encoder reading

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
    moveCCW(out);
  }
  else{
    moveCW(out);
  }
}

void moveCCW(int CCW){
  analogWrite(motor1pin1, CCW);
  analogWrite(motor1pin2, 0);
  //Serial.println(CCW);
  delay(50);
}

void moveCW(int CW){
  int moveCW = abs(CW);
  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, moveCW);
  //Serial.println(moveCW);
  delay(50);
}
