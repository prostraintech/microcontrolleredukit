/*
LED Demo Code
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

// Pin declaration
const int RGB_Red = 13;   //RGB LED
const int RGB_Blue = 12;
const int RGB_Green = 11;
const int LED_Green = 9;  //Single LED
const int ArrLED_1 = 6;   //Array LED
const int ArrLED_2 = 5;
const int ArrLED_3 = 4;
const int ArrLED_4 = 3;
const int ArrLED_5 = 2;
const int LatPB_1 = 1;    //Latching Buttons
const int LatPB_2 = 0;

// Global variable declaration
int brightness = 180;    
int fadeAmount = 3;
int ledMode = 0;

void setup() {
  // put your setup code here, to run once:
  // Digital Input
  /*Note:
    Due to the direct connection between digital pin to a pushbutton
    which the other end connected to GND, we need to use internal pullup
    for each digital input. The digital input reading will be inverted.
    Example: If input receive 5V, the reading in Arduino will display as 0/LOW
    and vice versa.
  */
  pinMode(LatPB_1,INPUT_PULLUP);
  pinMode(LatPB_2,INPUT_PULLUP);
  
  // Digital Output
  pinMode(RGB_Red,OUTPUT);
  pinMode(RGB_Blue,OUTPUT);
  pinMode(RGB_Green,OUTPUT);
  pinMode(LED_Green,OUTPUT);
  pinMode(ArrLED_1,OUTPUT);
  pinMode(ArrLED_2,OUTPUT);
  pinMode(ArrLED_3,OUTPUT);
  pinMode(ArrLED_4,OUTPUT);
  pinMode(ArrLED_5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Latching push button reading and LED mode selection
  if((digitalRead(LatPB_1)==LOW)&&(digitalRead(LatPB_2)==HIGH)){
    ledMode = 1;
  }
  else if((digitalRead(LatPB_1)==HIGH)&&(digitalRead(LatPB_2)==LOW)){
    ledMode = 2;
  }
  else if((digitalRead(LatPB_1)==LOW)&&(digitalRead(LatPB_2)==LOW)){
    ledMode = 3;
  }
  else{
    ledMode = 0;
  }

  // Led mode selection
  switch(ledMode){
    case 1:
    
    case 2:
    
    case 3:
    
    default:
    
  }

  
}
