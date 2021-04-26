// Libraries
#include <TimedAction.h>
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

// Functions for use in Timed Actions
void drive();
void grab();
void checkMotor();
void motorDistance();
void emergencyStop();

// Timed Actions
//TimedAction Motor = TimedAction(1, checkMotor);

// Pins
int capturePin = 22;
int ignorePin = 24;
int forwardPin = 26;
int leftPin = 28;
int rightPin = 30;

// Local temps
bool started = false;
bool driving = false;
bool drive_forward = false;

bool takingCommands = true;
int stepperLeftPos;
int stepperRightPos;

void setup() {

  stepperLeft.setSpeed(200);
  stepperLeft.setMaxSpeed(baseSpeed);
  stepperLeft.setAcceleration(baseAcceleration);

  stepperRight.setSpeed(200);
  stepperRight.setMaxSpeed(baseSpeed);
  stepperRight.setAcceleration(baseAcceleration);

  stepperLeft.moveTo(1000);
  stepperRight.moveTo(1500);

  // Microstrepping - Eightstep MS1:ON, MS2:ON, MS3:OFF
  pinMode(microstepPin1, OUTPUT);
  pinMode(microstepPin2, OUTPUT);
  pinMode(microstepPin3, OUTPUT);
  digitalWrite(microstepPin1, LOW);
  digitalWrite(microstepPin2, LOW);
  digitalWrite(microstepPin3, LOW);

  // Pin modes
  pinMode(capturePin, INPUT);
  pinMode(ignorePin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);

  setup_servos();

  // Serial
  Serial.begin(9600);

}

void loop() {

  stepperLeft.run();
  stepperRight.run();

  if(stepperLeft.currentPosition() == 1000 && stepperRight.currentPosition() == 1500) {
    grab();
  }
  
    
}
