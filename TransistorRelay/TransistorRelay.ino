// Demo code for Transistor and Darlington Transistor tutorial
// ProStrain Technologies
// By Taufik Yunahar
// Please contact us at info@prostrain.com.my if you have any inquiries.

const int proxSwitch = 2;
const int baseTransistor = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(baseTransistor, OUTPUT);
  pinMode(proxSwitch, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(proxSwitch)==HIGH){
    digitalWrite(baseTransistor,HIGH);
  }
  else{
    digitalWrite(baseTransistor,LOW);
  }
}
