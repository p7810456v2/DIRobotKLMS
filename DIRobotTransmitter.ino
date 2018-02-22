#include <SPI.h>
#include <RF24.h>

#define powerLevel RF24_PA_MIN //Change this to change
//the power level
#define rfTransmitPin 4 
const int upperThreshold = 70;  //upper threshold value
const int lowerThreshold = 50;  //lower threshold value

byte button;
int rfReceivePin;
int joyX;
int joyY;
int push = 0;
//unsigned int dat = analogRead(rfReceivePin);
RF24 radio(7,8); //CE, CSN

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(powerLevel);
  radio.openWritingPipe(0x0000000001);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  //pinMode(A2, INPUT);
  //pinMode(A3, INPUT);
  //pinMode(6, OUTPUT);
  radio.stopListening();
  pinMode(rfTransmitPin, OUTPUT); 
}

void loop() {
  joyX = analogRead(A0);
  joyY = analogRead(A1);
  push = digitalRead(A2);
  //Turn the joystick moves into hex vals to be sent
  if(joyY <= 250){
    button = 0x02;
  }
  else{
    if(joyY >= 750){
    button = 0x05;
    }
    else{
      if(joyX <= 250){
        button = 0x03;
      }
      else{
          if(joyX >= 750){
            button = 0x04;
          }
          /*else{
            if(digitalRead(A4) == HIGH){
              button = 0x06;
          }*/
            else{
              button = 0x01;
          }
           /*if(push == LOW){
             if(dat>upperThreshold){
                Serial.println(dat);
             }
             if(dat<lowerThreshold){   //If a HIGH signal is received, turn LED ON
                Serial.println(dat);
            }*/
          }
          
      }
    }
    
   
  //}
  /*for(int i=4000; i>5; i=i-(i/3)){
     digitalWrite(rfTransmitPin, HIGH);
     digitalWrite(rfTransmitPin,LOW);
  }
  
  /*if(digitalRead(A0) == LOW && digitalRead(A1) == LOW
  && digitalRead(A2) == LOW && digitalRead(A3) == LOW){
    button == 0x01;
  }*/

  //Output joystick info
  Serial.print("A0: ");
  Serial.print(analogRead(A0));
  Serial.print(" A1: ");
  Serial.println(analogRead(A1));
  
  if(!radio.write(&button, sizeof(byte))){
    digitalWrite(6, HIGH);
    Serial.print("It FAILED");
  }
  else{
    digitalWrite(6, LOW);
  }
}

