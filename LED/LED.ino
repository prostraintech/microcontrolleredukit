/*
LED Demo Code
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

//Pin declaration
const int RGB_Red = 13;
const int RGB_Blue = 12;
const int RGB_Green = 11;
const int LED_Green = 9;
const int ArrLED_1 = 6;
const int ArrLED_2 = 5;
const int ArrLED_3 = 4;
const int ArrLED_4 = 3;
const int ArrLED_5 = 2;

//Global variable declaration
int brightness = 180;    
int fadeAmount = 3;

void setup() {
  // put your setup code here, to run once:
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
  
}
