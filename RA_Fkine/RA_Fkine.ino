// Code for 2-Link Robotic Arm's forward kinematics(fkine). Moving arms simultaneously according to joint angles (deg) as input.
// ProStrain Technologies
// By Zharif Zubaidi
// Please contact us at info@prostrain.com.my if you have any inquiries.

// Define pin connections & motor's steps per revolution
const int dirPin1 = 2;
const int stepPin1 = 3;
const int dirPin2 = 4;
const int stepPin2 = 5;
int passInit = 0;
const int pulseDelay = 3000; //speed

void setup()
{
  // Joint 1
  pinMode(stepPin1, OUTPUT);
  digitalWrite(stepPin1, LOW);
  pinMode(dirPin1, OUTPUT);
  
  // Joint 2
  pinMode(stepPin2, OUTPUT);
  digitalWrite(stepPin2, LOW);
  pinMode(dirPin2, OUTPUT);

  // Set J1 direction counter clockwise 90 degree / another 756 steps
  digitalWrite(dirPin1, LOW);
  // Set J2 direction counter clockwise 62.56 degree / 556 steps
  digitalWrite(dirPin2, LOW);
  // Spin motor slowly
  for(int x = 0; x <= 756; x++)
  {
    digitalWrite(stepPin1, HIGH);
    if(x<=556){
    digitalWrite(stepPin2, HIGH);
    }
    delayMicroseconds(pulseDelay);
    digitalWrite(stepPin1, LOW);
    if(x<=556){
    digitalWrite(stepPin2, LOW);
    }
    delayMicroseconds(pulseDelay);  
  }
  delay(1000); // Wait a second

}
void loop()
{
  if (passInit == 0)
  {
  // (0,217.7) -> (100,130)
  // Set J1 direction clockwise 77.62 degree / 690 steps / TP -> 12.38 from J1 origin
  digitalWrite(dirPin1, HIGH);
  // Set J2 direction clockwise 82.25 degree / 731 steps / TP -> 82.25 from J2 origin
  digitalWrite(dirPin2, HIGH);
  // Spin motor slowly
  for(int x = 0; x <= 731; x++)
  {
    if(x<=690)
    {
    digitalWrite(stepPin1, HIGH);
    }
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(pulseDelay);
    
    if(x<=690)
    {
    digitalWrite(stepPin1, LOW);
    }
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(pulseDelay);  
    }
    delay(1000); // Wait a second
    
    passInit++;  // Increment passFlag
  }
  
  // (100,130) -> (60,190)
  // Set J1 direction counter clockwise 36.87 degree / 328 steps / TP -> 49.25 from J1 origin
  digitalWrite(dirPin1, LOW);
  // Set J2 direction counter clockwise 34.72 degree / 309 steps / TP -> 47.53 from J2 origin
  digitalWrite(dirPin2, LOW);
  // Spin motor slowly
  for(int x = 0; x <= 328; x++)
  {
    digitalWrite(stepPin1, HIGH);
    if(x<=309)
    {
      digitalWrite(stepPin2, HIGH);  
    }
    delayMicroseconds(pulseDelay);
    
    digitalWrite(stepPin1, LOW);
    if(x<=309)
    {
      digitalWrite(stepPin2, LOW);
    }
    delayMicroseconds(pulseDelay);  
    }
    delay(1000); // Wait a second

  // (60,190) -> (-60,190)
  // Set J1 direction counter clockwise 35.05 degree / 312 steps / TP -> 84.30 degree from J1 origin
  digitalWrite(dirPin1, LOW);
  // Set J2 direction 0 degree / 0 steps / TP -> 0 degree from J2 origin
  digitalWrite(dirPin2, LOW);
  // Spin motor slowly
  for(int x = 0; x <= 312; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(pulseDelay);
    
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(pulseDelay);  
    }
    delay(1000); // Wait a second

  // (-60,190) -> (-100,130)
  // Set J1 direction counter clockwise 3.22 degree / 29 steps / TP -> 87.52 degree from J1 origin
  digitalWrite(dirPin1, LOW);
  // Set J2 direction clockwise 34.72 degree / 309 steps / TP -> 82.25 degree from J2 origin
  digitalWrite(dirPin2, HIGH);
  // Spin motor slowly
  for(int x = 0; x <= 309; x++)
  {
    if(x<=29)
    {
      digitalWrite(stepPin1, HIGH);
    }
    digitalWrite(stepPin2, HIGH);  
    delayMicroseconds(pulseDelay);
    
    if(x<=29)
    {
      digitalWrite(stepPin1, LOW);
    }
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(3000);  
    }
    delay(1000); // Wait a second

  // (-100,130) -> (100,130)
  // Set J1 direction clockwise 75.14 degree / 668 steps / TP -> 12.38 degree from J1 origin
  digitalWrite(dirPin1, HIGH);
  // Set J2 direction 0 degree / 0 steps / TP -> 0 degree from J2 origin
  digitalWrite(dirPin2, LOW);
  // Spin motor slowly
  for(int x = 0; x <= 668; x++)
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(pulseDelay);
    
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(pulseDelay);  
    }
  delay(1000); // Wait a second
    
}
