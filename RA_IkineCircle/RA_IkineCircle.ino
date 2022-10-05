#include <SpeedyStepper.h> 
#include <math.h>

//Code for 2-Link Robotic Arm making a circle by using 36 points (increment of 10 degree)
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
int passInit = 0;

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
  //if (passMain != 1){
    if (passInit != 1){
      currentTheta1 = 90;
      currentTheta2 = 0;
      passInit++;
    }

  // Drawing a circle using 10 degree increments to get 36 points. Acceleration and decceleration are the same.

  //Point 1
  //Target position (X,Y)
  targetX = 40;
  targetY = 160;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 2
  //Target position (X,Y)
  targetX = 39;
  targetY = 167;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 3
  //Target position (X,Y)
  targetX = 38;
  targetY = 174;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 4
  //Target position (X,Y)
  targetX = 35;
  targetY = 180;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 5
  //Target position (X,Y)
  targetX = 31;
  targetY = 186;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 6
  //Target position (X,Y)
  targetX = 26;
  targetY = 191;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 7
  //Target position (X,Y)
  targetX = 20;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 8
  //Target position (X,Y)
  targetX = 14;
  targetY = 198;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 9
  //Target position (X,Y)
  targetX = 7;
  targetY = 199;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 10
  //Target position (X,Y)
  targetX = 1;
  targetY = 200;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 11
  //Target position (X,Y)
  targetX = -7;
  targetY = 199;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 12
  //Target position (X,Y)
  targetX = -14;
  targetY = 198;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 13
  //Target position (X,Y)
  targetX = -20;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1);
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 14
  //Target position (X,Y)
  targetX = -26;
  targetY = 191;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 15
  //Target position (X,Y)
  targetX = -31;
  targetY = 186;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 16
  //Target position (X,Y)
  targetX = -35;
  targetY = 180;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 17
  //Target position (X,Y)
  targetX = -38;
  targetY = 174;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);
  
  //Point 18
  //Target position (X,Y)
  targetX = -39;
  targetY = 167;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 19
  //Target position (X,Y)
  targetX = -40;
  targetY = 160;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 20
  //Target position (X,Y)
  targetX = -39;
  targetY = 153;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 21
  //Target position (X,Y)
  targetX = -38;
  targetY = 146;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 22
  //Target position (X,Y)
  targetX = -35;
  targetY = 140;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 23
  //Target position (X,Y)
  targetX = -31;
  targetY = 134;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 24
  //Target position (X,Y)
  targetX = -26;
  targetY = 129;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 25
  //Target position (X,Y)
  targetX = -20;
  targetY = 125;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 26
  //Target position (X,Y)
  targetX = -14;
  targetY = 122;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 27
  //Target position (X,Y)
  targetX = -7;
  targetY = 121;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 28
  //Target position (X,Y)
  targetX = 1;
  targetY = 120;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 29
  //Target position (X,Y)
  targetX = 7;
  targetY = 121;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 30
  //Target position (X,Y)
  targetX = 14;
  targetY = 122;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 31
  //Target position (X,Y)
  targetX = 20;
  targetY = 125;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 32
  //Target position (X,Y)
  targetX = 26;
  targetY = 129;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 33
  //Target position (X,Y)
  targetX = 31;
  targetY = 134;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 34
  //Target position (X,Y)
  targetX = 35;
  targetY = 140;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 35
  //Target position (X,Y)
  targetX = 38;
  targetY = 146;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 36
  //Target position (X,Y)
  targetX = 39;
  targetY = 153;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);

  //Point 37
  //Target position (X,Y)
  targetX = 40;
  targetY = 160;
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
  joint1.setSpeedInStepsPerSecond(jointSpeed);
  joint1.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint1.setupRelativeMoveInSteps(moveStep1); 
  
  //Joint 2
  joint2.setSpeedInStepsPerSecond(jointSpeed);
  joint2.setAccelerationInStepsPerSecondPerSecond(jointAccel);
  joint2.setupRelativeMoveInSteps(moveStep2);
  
  //Move the joints
  while((!joint1.motionComplete()) || (!joint2.motionComplete())){
    joint1.processMovement();
    joint2.processMovement();
  }
  //delay(1000);
  //passMain++;
  //}
}
