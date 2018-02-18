#include <SPI.h>
#include <RF24.h>

#define powerLevel RF24_PA_HIGH //Change this to change
//the power level

 byte button;

RF24 radio(7,8); //CE, CSN

void setup() {
  radio.begin();
  radio.setPALevel(powerLevel);
  radio.openWritingPipe(0x0000000001);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(6, OUTPUT);
  radio.stopListening();
}

void loop() {
  //Turn the button presses into hexadecimals to be sent
  if(digitalRead(A0) == HIGH){
    button = 0x02;
  }
  else{
    if(digitalRead(A1) == HIGH){
    button = 0x03;
    }
    else{
      if(digitalRead(A2) == HIGH){
        button = 0x04;
      }
      else{
          if(digitalRead(A3) == HIGH){
            button = 0x05;
          }
          else{
            if(digitalRead(A4) == HIGH){
              button = 0x06;
          }
            else{
              button = 0x01;
          }
      }
    }
    
   
  }
  /*if(digitalRead(A0) == LOW && digitalRead(A1) == LOW
  && digitalRead(A2) == LOW && digitalRead(A3) == LOW){
    button == 0x01;
  }*/
  
  if(!radio.write(&button, sizeof(byte))){
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}
}
