// Modules
#include <AccelStepper.h>

// Constants
// Left motor pins
const int stepPinLeft = 5; 
const int dirPinLeft = 4; 
// Right motor pins
const int stepPinRight = 7;
const int dirPinRight = 6;
// Other pins
const int microstepPin1 = 13;
const int microstepPin2 = 12;
const int microstepPin3 = 11;
// Values
const float baseSpeed = 200.0;
const float baseAcceleration = 100.0;

// Define steppers
AccelStepper stepperLeft(2, stepPinLeft, dirPinLeft);
AccelStepper stepperRight(2, stepPinRight, dirPinRight);

void setup_motors() {
  stepperLeft.setMaxSpeed(baseSpeed);
  stepperLeft.setAcceleration(baseAcceleration);

  stepperRight.setMaxSpeed(baseSpeed);
  stepperRight.setAcceleration(baseAcceleration);

  // Microstrepping - Eightstep MS1:ON, MS2:ON, MS3:OFF
  pinMode(microstepPin1, OUTPUT);
  pinMode(microstepPin2, OUTPUT);
  pinMode(microstepPin3, OUTPUT);
  digitalWrite(microstepPin1, LOW);
  digitalWrite(microstepPin2, LOW);
  digitalWrite(microstepPin3, LOW);

  stepperLeft.moveTo(2000);
  stepperRight.moveTo(2000);
}

void checkMotor() {
  
  stepperLeft.run();
  stepperRight.run();
  if(stepperLeft.distanceToGo() == 0 && stepperRight.distanceToGo() == 0) {

    stepperLeft.stop();
    stepperRight.stop();
    driving = false;
    
  }
  
}

void motorDistance(float left, float right) {

  stepperLeft.moveTo(stepperLeft.currentPosition() + left);
  stepperRight.moveTo(stepperRight.currentPosition() + right);
  
}

void emergencyStop() {

  stepperLeft.stop();
  stepperRight.stop();
  stepperLeft.moveTo(stepperLeft.currentPosition());
  stepperRight.moveTo(stepperRight.currentPosition());
  driving = false;
  
}

void drive(float point) {
  //stepperLeft.moveTo(point);
  //stepperRight.moveTo(point);
  stepperLeft.runSpeed();
  stepperRight.runSpeed();
}

void reverse(float point) {
  stepperLeft.moveTo(point);
  stepperRight.moveTo(point);
  stepperLeft.run();
  stepperRight.run();
}

void turn(float deg) {
  stepperLeft.moveTo(deg);
  stepperRight.moveTo(deg);
  stepperLeft.run();
  stepperRight.run();
}
