 /*The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Define Pins. Constants won't change. They're used here to set pin numbers. Pin 20 & 21 is interrupt
const int EncoderPinA = 2;   // Encoder Pin A. Interrupt 2
const int EncoderPinB = 3;  // Encoder Pin B. Interrupt 3
//Initialize Variables
volatile int counts = 0; //counts the encoder counts. The encoder has counts/rev

void setup(){
  Serial.begin(115200);
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, HIGH); //initialize Pin States
  digitalWrite(EncoderPinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), readEncoder, CHANGE); //attach interrupt to PIN 21
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
  lcd.setCursor(0, 1);
  lcd.print(counts);
  
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  lcd.clear();
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts+1;
  }
}
