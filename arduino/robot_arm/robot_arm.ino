/*
 * Name:       robotic_arm.ino
 * Created:    2020-03-10
 * Author:     Alexandre Desgagné
 */

#include <Servo.h> 

enum State {control = 1, record = 2};

// Variables
String input;
State mState;
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // current position
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // previous 

// LEDs
int mControlLedPin = 2;
int mRecordLedPin = 7;
int mWorkingLedPin = 4;

// Servos
Servo mGripper;
Servo mWristPitch;
Servo mWristRoll;
Servo mElbow;
Servo mShoulder;
Servo mWaist;

// Function to set control state LED.
void setControlStateLed(){
  digitalWrite(mControlLedPin, HIGH);
  digitalWrite(mRecordLedPin, LOW);
}

// Function to set record state LED.
void setRecordStateLed(){
  digitalWrite(mControlLedPin, LOW);
  digitalWrite(mRecordLedPin, HIGH);
}

/*
 * Function to set specified servo position.
 * index: Servo index.
 * pos: Servo position.
 */
void moveServo(int index, int pos){
  if (mState == State::control){
     String toPrint = "Servo: " + String(index) + ", Pos: " + String(pos);
     Serial.println(toPrint);
     switch(index){
      case 1:
        servo1Pos = pos;
        if (servo1PPos > servo1Pos) {
          for ( int j = servo1PPos; j >= servo1Pos; j--) {
            mGripper.write(j);
            delay(30);
          }
        }
        if (servo1PPos < servo1Pos) {
          for ( int j = servo1PPos; j <= servo1Pos; j++) {
            mGripper.write(j);
            delay(30);
          }
        }
        servo1PPos = servo1Pos;
        break;
      case 2:
        servo2Pos = pos;
        if (servo2PPos > servo2Pos) {
          for ( int j = servo2PPos; j >= servo2Pos; j--) {
            mWristPitch.write(j);
            delay(30);
          }
        }
        if (servo2PPos < servo2Pos) {
          for ( int j = servo2PPos; j <= servo2Pos; j++) {
            mWristPitch.write(j);
            delay(30);
          }
        }
        servo2PPos = servo2Pos;
        break;
      case 3:
        servo3Pos = pos;
        if (servo3PPos > servo3Pos) {
          for ( int j = servo3PPos; j >= servo3Pos; j--) {
            mWristRoll.write(j);
            delay(30);
          }
        }
        if (servo3PPos < servo3Pos) {
          for ( int j = servo3PPos; j <= servo3Pos; j++) {
            mWristRoll.write(j);
            delay(30);
          }
        }
        servo3PPos = servo3Pos;
        break;
      case 4:
        servo4Pos = pos;
        if (servo4PPos > servo4Pos) {
          for ( int j = servo4PPos; j >= servo4Pos; j--) {
            mElbow.write(j);
            delay(30);
          }
        }
        if (servo4PPos < servo4Pos) {
          for ( int j = servo4PPos; j <= servo4Pos; j++) {
            mElbow.write(j);
            delay(30);
          }
        }
        servo4PPos = servo4Pos;
        break;
      case 5:
        servo5Pos = pos;
        if (servo5PPos > servo5Pos) {
          for ( int j = servo5PPos; j >= servo5Pos; j--) {
            mShoulder.write(j);
            delay(30);
          }
        }
        if (servo5PPos < servo5Pos) {
          for ( int j = servo5PPos; j <= servo5Pos; j++) {
            mShoulder.write(j);
            delay(30);
          }
        }
        servo5PPos = servo5Pos;
        break;
      case 6:
        servo6Pos = pos;
        if (servo6PPos > servo6Pos) {
          for ( int j = servo6PPos; j >= servo6Pos; j--) {
            mWaist.write(j);
            delay(30);
          }
        }
        if (servo6PPos < servo6Pos) {
          for ( int j = servo6PPos; j <= servo6Pos; j++) {
            mWaist.write(j);
            delay(30);
          }
        }
        servo6PPos = servo6Pos;
        break;
      default:
        break;
    } 
  }
}

// Function to flash working lED for fun.
void sayHello(int timeCount){
  for(int i = 0; i < timeCount; ++i){
    digitalWrite(mWorkingLedPin, HIGH);
    delay(100);
    digitalWrite(mWorkingLedPin, LOW);
    delay(100);
  }
  digitalWrite(mWorkingLedPin, HIGH);
}

// Initial setup.
void setup(){
  // LEDs
  pinMode(mControlLedPin, OUTPUT);
  pinMode(mRecordLedPin, OUTPUT);
  pinMode(mWorkingLedPin, OUTPUT);

  // Servos
  mGripper.attach(3);
  mWristPitch.attach(5);
  mWristRoll.attach(6);
  mElbow.attach(9);
  mShoulder.attach(10);
  mWaist.attach(11);
  
  // Serial setup.
  Serial.begin(9600);
  delay(20);
  // Initial state.
  mState = State::control;
  setControlStateLed();

  servo1PPos = 120;
  mGripper.write(servo1PPos);

  // Working LED started.
  digitalWrite(mWorkingLedPin, HIGH);
}

// Main program loop.
void loop(){
  if (Serial.available()){
    char carac = Serial.read();
    if (carac == ';'){
      if (input.length() > 1) {
        int value = input.toInt(); // Parse value from input.

        // Select the servo and send the pos from the input code.
        if(input.indexOf('a') > 0){ moveServo(1, value); }
        if(input.indexOf('b') > 0){ moveServo(2, value); }
        if(input.indexOf('c') > 0){ moveServo(3, value); }
        if(input.indexOf('d') > 0){ moveServo(4, value); }
        if(input.indexOf('e') > 0){ moveServo(5, value); }
        if(input.indexOf('f') > 0){ moveServo(6, value); }
        
        // Mode switch control/record.
        if(input.indexOf('m') > 0){
          if(value == 1){
            // Switch to control mode.
            mState = State::control;
            setControlStateLed();
          }
          else if (value == 2){
            // Switch to record mode.
            mState = State::record;
            setRecordStateLed();
          }
        }

        //Say hello feature.
        if(input.indexOf('p') > 0){ sayHello(value); }

        // Erase input.
        input = "";
      }
    }
    else{
      input += carac;
    }
  }
}
