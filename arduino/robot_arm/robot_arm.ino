/*
    Name:       robotic_arm.ino
    Created:  2020-03-10
    Author:     Alexandre Desgagné
*/

#include <Servo.h>

int val{ 0 };
Servo servoRotation;

void setup()
{
  servoRotation.attach(2);
}

void loop()
{
  val = 0;
  servoRotation.write(val);
  delay(3000);
  val = 90;
  servoRotation.write(val);
  delay(3000);
}
