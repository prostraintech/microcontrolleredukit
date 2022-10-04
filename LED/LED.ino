/*
LED Demo Code
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

// Pin declaration
const int RGB_Red = 11;   //RGB LED Common Cathode
const int RGB_Blue = 10;
const int RGB_Green = 9;
const int LED_Green = 3;  //Single LED
const int ArrLED_1 = 4;   //Array LED
const int ArrLED_2 = 5;
const int ArrLED_3 = 6;
const int ArrLED_4 = 7;
const int ArrLED_5 = 8;
const int LatPB_1 = 1;    //Latching Buttons
const int LatPB_2 = 0;

// Global variable declaration
int brightness = 0;    
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
      colorRGB(255, 0, 0);     // Red
      delay(500);
      colorRGB(0, 255, 0);     // Green
      delay(500);
      colorRGB(0, 0, 255);     // Blue
      delay(500);
      colorRGB(0, 255, 255);   // Cyan
      delay(500);
      colorRGB(255, 255, 0);   // Yellow
      delay(500);
      colorRGB(255, 0, 255);   // Purple
      delay(500);
      colorRGB(255, 255, 255); // White
      delay(500);
      break;
    case 2:
      analogWrite(LED_Green, brightness);
      //digitalWrite(LED_Green, HIGH);
      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;
    
      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255){
        fadeAmount=-fadeAmount;
      }
      // wait for 30 milliseconds to see the dimming effect
      break;
    case 3:
      arrayLED(1,0,0,0,0);
      delay(500);
      arrayLED(1,1,0,0,0);
      delay(500);
      arrayLED(1,1,1,0,0);
      delay(500);
      arrayLED(1,1,1,1,0);
      delay(500);
      arrayLED(1,1,1,1,1);
      delay(500);
      arrayLED(0,0,0,0,0);
      delay(250);
      arrayLED(1,1,1,1,1);
      delay(250);
      arrayLED(1,1,1,1,1);
      delay(250);
      arrayLED(0,0,0,0,0);
      delay(1000);
      break;
    default:
      //Turn off LED
      colorRGB(0, 0, 0); //RGB Led
      digitalWrite(LED_Green,LOW);
      arrayLED(0,0,0,0,0);
      break;
  }
  delay(30);
}

//RGB LED Function
// You can check RGB Colour Gradient - https://www.101computing.net/arduino-rgb-gradient/ 
void colorRGB(int red_value, int green_value, int blue_value){
  analogWrite(RGB_Red,red_value);
  analogWrite(RGB_Green,green_value);
  analogWrite(RGB_Blue,blue_value);
}

//LED Array Function
void arrayLED(int arrLED1, int arrLED2, int arrLED3, int arrLED4, int arrLED5){
  digitalWrite(ArrLED_1,arrLED1);
  digitalWrite(ArrLED_2,arrLED2);
  digitalWrite(ArrLED_3,arrLED3);
  digitalWrite(ArrLED_4,arrLED4);
  digitalWrite(ArrLED_5,arrLED5);
}
