#include <AFMotor.h> //Library for motors
#include <SPI.h> //Default SPI library
#include <RF24.h> //Library for the radio

#define powerLevel RF24_PA_LOW /*Change this to change
the radio power level*/

#define transPin A8

AF_DCMotor motor1(1); //Set up motors
AF_DCMotor motor2(2); //Set up motors
AF_DCMotor motor3(3); //Set up motors
AF_DCMotor motor4(4); //Set up motors

RF24 radio(49, 48); //CE, CSN

long prevMillis = 0;
int transState = LOW;
unsigned long prevMills = 0;
const long interval = 10;
byte recievedPayload; /* The payload recieved from
the controller*/

/*byte address[6]; Address for the radio
pipe, 40-bit, so 10 hexadecimal numbers, array should be
5 bytes long, but set to 6 just in case*/

void setup() {
  pinMode(transPin, OUTPUT);
  pinMode(13, OUTPUT);
  radio.begin();
  radio.setPALevel(powerLevel);
  radio.openReadingPipe(1, 0x0000000001);
  radio.startListening();

  motor1.setSpeed(200); //Set the motor speeds
  motor2.setSpeed(200); //Set the motor speeds
  motor3.setSpeed(200); //Set the motor speeds
  motor4.setSpeed(200); //Set the motor speeds
}

void loop() {
  unsigned long currMillis = millis();
  if(radio.available()){
    radio.read(&recievedPayload, sizeof(byte));
    digitalWrite(13, HIGH);
    }
  else{
    digitalWrite(13, LOW);
  }
  if(currMillis - prevMillis > interval){
    prevMillis = currMillis;
  }
  if(transState == LOW){
    transState = HIGH;
  } else {
    transState = LOW;
  }
  
  switch(recievedPayload){ //Switch payload into motors
    case 0x01:
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    break;

    case 0x02:
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    break;

    case 0x03:
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    break;

    case 0x04:
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    break;

    case 0x05:
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    break;
    
  }
}
/*  Unnecessary for now...
void motor(byte motorNumber, byte motorSpeed){
  //Reverse = 0, Stop = 1, Forward = 3
  if(motorSpeed == 3){
    switch(motorSpeed){
      case 0:
        switch(motorNumber){
          case 1:
            digitalWrite(22, LOW);
            digitalWrite(23, LOW);
            break;
          case 2:
            digitalWrite(24, LOW);
            digitalWrite(25, LOW);
            break;
          case 3:
            digitalWrite(26, LOW);
            digitalWrite(27, LOW);
            break;
          case 4:
            digitalWrite(28, LOW);
            digitalWrite(29, LOW);
            break;
        }
        }
    }
  }
}*/
