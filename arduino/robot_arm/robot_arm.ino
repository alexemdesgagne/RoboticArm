/*
 * Name:       robotic_arm.ino
 * Created:    2020-03-10
 * Author:     Alexandre Desgagné
 */

enum State {control = 1, record = 2};

// Variables
int mControlLedPin = 2;
int mRecordLedPin = 3;
int mWorkingLedPin = 4;
String input;
State mState;

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
  String toPrint = "Servo: " + String(index) + ", Pos: " + String(pos);
  Serial.println(toPrint);
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
  
  // Serial setup.
  Serial.begin(9600);

  // Initial state.
  mState = State::control;
  setControlStateLed();

  // Working LED started.
  digitalWrite(mWorkingLedPin, HIGH);
}

// Main program loop.
void loop(){
  if (Serial.available()){
    char carac = Serial.read();
    if (carac == ';'){
      if (input.length() > 1) {
        Serial.println(input);
        
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
