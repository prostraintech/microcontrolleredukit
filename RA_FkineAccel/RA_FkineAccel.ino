// Code for 2-Link Robotic Arm's forward kinematics + acceleration and decelaration.
// ProStrain Technologies
// By Zharif Zubaidi
// Please contact us at info@prostrain.com.my if you have any inquiries.

// Include library
#include <SpeedyStepper.h> 

// Define pin connections & motor's steps per revolution
#define DIRPIN1 2
#define STEPPIN1 3
#define DIRPIN2 4
#define STEPPIN2 5
int passInit = 0;
int passMain = 0;

SpeedyStepper joint1;
SpeedyStepper joint2;

void setup(){
  joint1.connectToPins(STEPPIN1,DIRPIN1);
  joint2.connectToPins(STEPPIN2,DIRPIN2);
}

void loop(){
  if(passInit == 0){
    //Initialisation movement
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    //Set Joint 1 direction counter clockwise 90 degree / 756 steps
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(756); //CCW is a positive movement
  
    //Joint 2
    //Set J2 direction counter clockwise 62.56 degree / 556 steps
    joint2.setSpeedInStepsPerSecond(700);
    joint2.setAccelerationInStepsPerSecondPerSecond(1000);
    joint2.setupRelativeMoveInSteps(556);//CCW is a positive movement
  
    //Move the joints from starting pose to initial pose (0,217.7)
      while((!joint1.motionComplete()) || (!joint2.motionComplete()))
    {
      joint1.processMovement();
      joint2.processMovement();
    }
  
    passInit++;
    delay(1000);
  }
  
  if(passMain == 0){

    //From (0,217.7) -> (100,130)
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    // Set J1 direction clockwise 77.62 degree / 690 steps / TP -> 12.38 from J1 origin
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(-690); //CW is a negative movement
  
    //Joint 2
    // Set J2 direction clockwise 82.25 degree / 731 steps / TP -> 82.25 from J2 origin
    joint2.setSpeedInStepsPerSecond(700);
    joint2.setAccelerationInStepsPerSecondPerSecond(1000);
    joint2.setupRelativeMoveInSteps(-731);//CW is a negative movement
  
    //Move the joints
      while((!joint1.motionComplete()) || (!joint2.motionComplete()))
    {
      joint1.processMovement();
      joint2.processMovement();
    }
    delay(1000); 
    passMain++;
   }

   
    //From (100,130) -> (60,190)
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    // Set J1 direction counter clockwise 36.87 degree / 328 steps / TP -> 49.25 from J1 origin
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(328); //CCW is a positive movement
  
    //Joint 2
    // Set J2 direction counter clockwise 34.72 degree / 309 steps / TP -> 47.53 from J2 origin
    joint2.setSpeedInStepsPerSecond(700);
    joint2.setAccelerationInStepsPerSecondPerSecond(1000);
    joint2.setupRelativeMoveInSteps(309);//CCW is a positive movement
  
    //Move the joints
      while((!joint1.motionComplete()) || (!joint2.motionComplete()))
    {
      joint1.processMovement();
      joint2.processMovement();
    }
    delay(1000);
    
    //From (60,190) -> (-60,190)
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    // Set J1 direction counter clockwise 35.05 degree / 312 steps / TP -> 84.30 degree from J1 origin
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(312); //CCW is a positive movement
  
    //Joint 2
    // Set J2 direction 0 degree / 0 steps / TP -> 0 degree from J2 origin
  
    //Move the joints
      while(!joint1.motionComplete())
    {
      joint1.processMovement();
    }
    delay(1000);
    
    //From (-60,190) -> (-100,130)
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    // Set J1 direction counter clockwise 3.22 degree / 29 steps / TP -> 87.52 degree from J1 origin
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(29); //CCW is a positive movement
  
    //Joint 2
    // Set J2 direction clockwise 34.72 degree / 309 steps / TP -> 82.25 degree from J2 origin
    joint2.setSpeedInStepsPerSecond(700);
    joint2.setAccelerationInStepsPerSecondPerSecond(1000);
    joint2.setupRelativeMoveInSteps(-309);//CW is a negative movement
  
    //Move the joints
      while((!joint1.motionComplete()) || (!joint2.motionComplete()))
    {
      joint1.processMovement();
      joint2.processMovement();
    }
    delay(1000);

    //(-100,130) -> (100,130)
    //Setup the speed, acceleration and number of steps to move for the motor
    //Joint 1
    // Set J1 direction clockwise 75.14 degree / 668 steps / TP -> 12.38 degree from J1 origin
    joint1.setSpeedInStepsPerSecond(700);
    joint1.setAccelerationInStepsPerSecondPerSecond(1000);
    joint1.setupRelativeMoveInSteps(-668); //CW is a negative movement
  
    //Joint 2
    // Set J2 direction 0 degree / 0 steps / TP -> 0 degree from J2 origin
  
    //Move the joints
      while((!joint1.motionComplete()))
    {
      joint1.processMovement();
    }
    delay(1000);
    
    //passMain++;
  //}
}
