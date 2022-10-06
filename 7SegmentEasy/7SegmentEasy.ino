/*
7 Segment LED Code
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

#include "SevSeg.h"
SevSeg sevseg; 

void setup(){
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};            // Digit 1 to 4
  byte segmentPins[] = {9, 8, 7, 6, 5, 4, 3, 2};  // A,B,C,D,E,F,G,DP

  bool resistorsOnSegments = true; 
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
    sevseg.setNumber(1234, 3);
    sevseg.refreshDisplay(); 
}
