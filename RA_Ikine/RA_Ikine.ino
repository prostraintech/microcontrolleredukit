#include <SpeedyStepper.h> 
#include <math.h>
//Code for 2-Link Robotic Arm's inverse kinematics (ikine). Using X-Y coordinate to move robotic arm.
// ProStrain Technologies
// By Zharif Zubaidi
// Please contact us at info@prostrain.com.my if you have any inquiries.

// Define pin connections & motor's steps per revolution
#define DIRPIN1 2
#define STEPPIN1 3
#define DIRPIN2 4
#define STEPPIN2 5

//Robot link length in mm
const double l1 = 111.2;
const double l2 = 106.5; 

int jointSpeed = 700;
int jointAccel = 1000;
int passMain = 0;

double targetX = 0;
double targetY = 0;
double l3 = 0;

// Joint angles are in degrees
double theta1 = 0;
double theta2 = 0;
double currentTheta1 = 0;
double currentTheta2 = 0;
double moveTheta1 = 0;
double moveTheta2 = 0;
int moveStep1 = 0;
int moveStep2 = 0;

SpeedyStepper joint1;
SpeedyStepper joint2;

void setup() {
  Serial.begin(9600);
  //Set up the step and direction pin for each joint
  joint1.connectToPins(STEPPIN1,DIRPIN1);
  joint2.connectToPins(STEPPIN2,DIRPIN2);
  
  //Initialisation movement (From neutral position to initial position (0,217.7))
  //Setup the speed, acceleration and number of steps to move for the motor
  //Joint 1
  //Set Joint 1 direction counter clockwise 90 degree / 756 steps
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(756); //CCW is a positive movement
  
  //Joint 2
  //Set J2 direction counter clockwise 62.56 degree / 556 steps
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(556);//CCW is a positive movement
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  delay(1000);
}

void loop() {
  if (passMain != 1){
    
  //From (0,217.7) -> (100,130)
  //Target position (X,Y)
  targetX = 100;
  targetY = 130;
  l3 = sqrt(sq(targetX)+sq(targetY));
  
  if (passMain != 1){
    currentTheta1 = 90;
    currentTheta2 = 0;
  }
  
  // Compute joint angles from end effector coordinate using inverse kinematics (ikine)
  if(targetX>0){
    //Quadrant 1 (x,y)
    theta1 = degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  } else{
    //Quadrant 2 (-x,y)
    theta1 = 180+degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  }

  // Movement needed to achieve target position
  moveTheta1 = theta1 - currentTheta1;
  moveTheta2 = currentTheta2 - theta2;
  moveStep1 = round(moveTheta1/360*3200); // 200*16=3200 steps due to microstepping
  moveStep2 = round(moveTheta2/360*3200);
  currentTheta1 = theta1;
  currentTheta2 = theta2;
  
  //Setup the speed, acceleration and number of steps to move for the motor
  //Joint 1
  // Set J1 direction clockwise 77.62 degree / 690 steps / TP -> 12.38 from J1 origin
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); //CW is a negative movement
  
  //Joint 2
  // Set J2 direction clockwise 82.25 degree / 731 steps / TP -> 82.25 from J2 origin
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);//CW is a negative movement
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  delay(1000);

  //From (100,130) -> (60,190)
  //Target position (X,Y)
  targetX = 1;
  targetY = 195;
  l3 = sqrt(sq(targetX)+sq(targetY));
  // Compute joint angles from end effector coordinate using inverse kinematics (ikine)
  if(targetX>0){
    //Quadrant 1 (x,y)
    theta1 = degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  } else{
    //Quadrant 2 (-x,y)
    theta1 = 180+degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  }

  // Movement needed to achieve target position
  moveTheta1 = theta1 - currentTheta1;
  moveTheta2 = currentTheta2 - theta2;
  moveStep1 = round(moveTheta1/360*3200); // 200*16=3200 steps due to microstepping
  moveStep2 = round(moveTheta2/360*3200);
  currentTheta1 = theta1;
  currentTheta2 = theta2;
  
  //Setup the speed, acceleration and number of steps to move for the motor
  //Joint 1
  // Set J1 direction counter clockwise 36.87 degree / 328 steps / TP -> 49.25 from J1 origin
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); //CW is a negative movement
  
  //Joint 2
  // Set J2 direction counter clockwise 34.72 degree / 309 steps / TP -> 47.53 from J2 origin
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);//CW is a negative movement
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  delay(1000);

    //From (100,130) -> (60,190)
  //Target position (X,Y)
  targetX = -29;
  targetY = 190;
  l3 = sqrt(sq(targetX)+sq(targetY));
  // Compute joint angles from end effector coordinate using inverse kinematics (ikine)
  if(targetX>0){
    //Quadrant 1 (x,y)
    theta1 = degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  } else{
    //Quadrant 2 (-x,y)
    theta1 = 180+degrees(atan(targetY/targetX)-acos((sq(l1)+sq(l3)-sq(l2))/(2*l1*l3)));
    theta2 = 180-degrees(acos((sq(l1)+sq(l2)-sq(l3))/(2*l1*l2)));
  }

  // Movement needed to achieve target position
  moveTheta1 = theta1 - currentTheta1;
  moveTheta2 = currentTheta2 - theta2;
  moveStep1 = round(moveTheta1/360*3200); // 200*16=3200 steps due to microstepping
  moveStep2 = round(moveTheta2/360*3200);
  currentTheta1 = theta1;
  currentTheta2 = theta2;
  
  //Setup the speed, acceleration and number of steps to move for the motor
  //Joint 1
  // Set J1 direction counter clockwise 36.87 degree / 328 steps / TP -> 49.25 from J1 origin
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); //CW is a negative movement
  
  //Joint 2
  // Set J2 direction counter clockwise 34.72 degree / 309 steps / TP -> 47.53 from J2 origin
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);//CW is a negative movement
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  delay(1000);
   
  passMain++;
  }
}
