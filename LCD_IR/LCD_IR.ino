/*
LCD-IR Demo Code
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int irPin = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("IR Sensor Distance Reading (cm):");
}

void loop() {
  //IR Reading
  float volts = analogRead(irPin)*0.0048828125; //(5/1024)
  int distance = 13*pow(volts,-1); //Volts^-1
  delay(500);
  if(distance <= 30){
    lcd.clear();
    delay(1);
    //LCD Displaying Sensor reading
    lcd.setCursor(0, 0);
    lcd.print("IR Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance);
  }
  else{
    lcd.clear();
    delay(1);
    lcd.setCursor(0, 0);
    lcd.print("IR Distance:");
    lcd.setCursor(0, 1);
    lcd.print("Out of range");
  }
}
