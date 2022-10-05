/*
Bluetooth HM10 Demo Code
BluetoothB Code which is the secondary arduino to receive instruction to control
a LED and Buzzer
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

//Library declaration
#include <SoftwareSerial.h>
SoftwareSerial HM10(0, 1); // RX = 0, TX = 1

//Pin declaration
const int ledPin = 4;
const int buzzPin = 5;

//Variable declaration
int recvInt;

void setup()
{
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  //Input reading will be inverted due to internal pullup. 0 means ON, 1 means OFF.
  pinMode(ledPin,OUTPUT);
  pinMode(buzzPin,OUTPUT);
}

void loop()
{
  //Run if HM10 receive any data
  if(HM10.available()>0){
    //Read data and store it
    recvInt=HM10.parseInt();
    Serial.println(recvInt);
  }
  //delay(30);
}
