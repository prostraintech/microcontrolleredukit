/*
Bluetooth HM10 Demo Code
BluetoothA Code which is the main arduino to send instruction based on
selector switch input.
ProStrain Technologies
By Zharif Zubaidi
Please contact us at info@prostrain.com.my if you have any inquiries.
*/

//Library declaration
#include <SoftwareSerial.h>
SoftwareSerial HM10(0, 1); // RX = 0, TX = 1

//Pin declaration
const int sltSW1 = 2;
const int sltSW2 = 3;

//Variable declaration
int sltSW1_state = 0;
int sltSW2_state = 0;
int sendByte;
int sendByte1;
int sendByte2;

void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  //Input reading will be inverted due to internal pullup. 0 means ON, 1 means OFF.
  pinMode(sltSW1,INPUT_PULLUP);
  pinMode(sltSW2,INPUT_PULLUP);
}

void loop()
{
  //Reading pin state
  sltSW1_state = digitalRead(sltSW1);
  sltSW2_state = digitalRead(sltSW2);

  //Send instruction in the form char to Arduino B using bluetooth
  //Updating byte before sending over bluetooth. First bit is Select Switch 1 bit
  //and second bit is Select Switch 2 bit.
  if(sltSW1_state==HIGH){
    sendByte1 = 1;
  }
  else{
    sendByte1 = 0;
  }

  if(sltSW2_state==HIGH){
    sendByte2 = 1<<1;
  }
  else{
    sendByte2 = 0<<1;
  }

  //Combining bit in one message and then send it using print. Can use write too. 
  //Refer to SoftwareSerial documentation 
  //by Arduino
  sendByte = sendByte1 + sendByte2;
  HM10.write(sendByte);
  
  delay(30);
}
