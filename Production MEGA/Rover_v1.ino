// Libraries
#include <TimedAction.h>

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

  // Pin modes
  pinMode(capturePin, INPUT);
  pinMode(ignorePin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);

  // Setups
  setup_motors();
  //setup_servos();

  // Serial
  Serial.begin(9600);

}

void loop() {

  // Always stop when capturing
  if(digitalRead(capturePin) == HIGH) {
    
    emergencyStop();
        
  }

    if(!driving) {

      if(digitalRead(forwardPin) == HIGH) {

        driving = true;

        motorDistance(2000, 2000);
        
      }

      if(digitalRead(ignorePin) == HIGH) {

        driving = true;

        motorDistance(0, 0);
        
      }

      if(digitalRead(leftPin) == HIGH) {

        driving = true;

        motorDistance(100, 0);
        
      }

      if(digitalRead(rightPin) == HIGH) {

        driving = true;

        motorDistance(0, 100);

      }
      
    }


    if(driving) {
      checkMotor();
    }
    
}
