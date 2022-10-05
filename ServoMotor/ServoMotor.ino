// Demo code for servo motor tutorial
// ProStrain Technologies
// By Zharif Zubaidi
// Please contact us at info@prostrain.com.my if you have any inquiries.

#include <Servo.h>

Servo servo_1; // servo controller (multiple can exist)
//Pin declaration
const int servo_pin = 3; // PWM pin for servo control
const int latchButton = 8;
//Variable declaration
int pos = 0;    // servo starting position

void setup() {
  servo_1.attach(servo_pin); // start servo control
  servo_1.write(-10); 
  pinMode(latchButton,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(latchButton)==LOW){
    // Move from 0 deg to 180 deg
    for (pos = 0; pos <= 180; pos += 1) { 
      // in steps of 1 degree
      servo_1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15); // delay to allow the servo to reach the desired position
      if (pos==90){
        delay(2000); //wait 2 seconds once positioned at 90 degrees
      }
    }
    delay(2000); // wait 2 seconds after reaching 180 degrees

    // Move from 0 deg to 180 deg
    for (pos = 180; pos >= 0; pos -= 1) {
      servo_1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      if (pos==90){
        delay(2000); // wait 2 seconds once positioned at 90 degrees
      }
    }
    delay(2000); // wait 2 seconds after arriving back at 0 degrees
  }
}
