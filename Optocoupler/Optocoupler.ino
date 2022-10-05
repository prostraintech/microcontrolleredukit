// ProStrain Technologies
// By Taufik Yunahar
// Please contact us at info@prostrain.com.my if you have any inquiries.
const int redLED = 13;
const int blueLED = 12;
const int optoIn1 = 4;
const int optoIn2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  //When using optocoupler and connect to Arduino digital input,
  //need to use internal pullup.
  pinMode(optoIn1, INPUT_PULLUP); // Input from 12V NC Emergency Stop
  pinMode(optoIn2, INPUT_PULLUP); // Input from 24V NO Emergency Stop
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(optoIn1)==HIGH){
    digitalWrite(redLED,HIGH);
  }
  else{
    digitalWrite(redLED,LOW);
  }
  if(digitalRead(optoIn2)==HIGH){
    digitalWrite(blueLED,HIGH);
  }
  else{
    digitalWrite(blueLED,LOW);
  }

}
