#include <SpeedyStepper.h> 
#include <math.h>

//Code for 2-Link Robotic Arm making a circle by using changeable resolution
//By Zharif Zubaidi (zharif.z@prostrain.com.my | ProStrain Technologies Sdn Bhd)

// Define pin connections & motor's steps per revolution
#define DIRPIN1 2
#define STEPPIN1 3
#define DIRPIN2 4
#define STEPPIN2 5
#define EE 6

//Robot link length in mm
const double l1 = 111.2;
const double l2 = 106.5; 

int jointSpeed = 700;
int jointAccel = 1000;
int passMain = 0;
int passInit = 0;
int passEE = 0;

double targetX = 0;
double targetY = 0;
double l3 = 0;

// Robot joint angles are in degrees
double theta1 = 0;
double theta2 = 0;
double currentTheta1 = 0;
double currentTheta2 = 0;
double moveTheta1 = 0;
double moveTheta2 = 0;
int moveStep1 = 0;
int moveStep2 = 0;


//Setting the robot joints
SpeedyStepper joint1;
SpeedyStepper joint2;

//Circle parameter
double originX = 0;
double originY = 0;
double radiusCircle = 0;
double resoCircle = 0;
double angleCircle = 0;
double xCircle = 0;
double yCircle = 0;
double incCircle = 0;
int drawSpeed = 0;

void setup() {
  Serial.begin(9600);
  //Setting up the end-effector
  pinMode(EE, OUTPUT);
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
  delay(500);
}

void loop() {
  //Initial position at J1 = 90deg & J2 = 0deg.
    if (passInit != 1){
      currentTheta1 = 90;
      currentTheta2 = 0;
      passInit++;
    }

  if (passMain != 1){
  //Path Planning
  //Dividing circle by desirable number of points to get the angle increment. Using angle increment,
  //we will get the X and Y coordinate for the circles by implementing polar coordinate formula.
  
  //Input from user for circle
  originX = 10;
  originY = 160;
  radiusCircle = 40;
  resoCircle = 361;
  angleCircle = 0;
  xCircle = 0;
  yCircle = 0;
  drawSpeed = 1000;
  
  //Processing the robot path
  incCircle = 360/resoCircle;
  
  for(int i = 0; i<=resoCircle; i++){
    xCircle = radiusCircle * cos(radians(angleCircle)) + originX;
    yCircle = radiusCircle * sin(radians(angleCircle)) + originY;
    Serial.println(i);
    Serial.print("X-Circle: ");
    Serial.println(xCircle);
    Serial.print("Y-Circle: ");
    Serial.println(yCircle);
    angleCircle = angleCircle + incCircle;

    //Robot movement based on coordinates that form a circle
    //Target end-effector position (X,Y)
    targetX = xCircle;
    targetY = yCircle;
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

    if (passEE != 1){
      analogWrite(LED_BUILTIN, 255);
      delay(1000);
      analogWrite(LED_BUILTIN,100);
      delay(1000);
      passEE++;
    }
    
    delay(drawSpeed);
  }
  
  passMain++;
  }
}
