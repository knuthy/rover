// Modules
#include <Servo.h>

// Constants
// Big servo pin
int bigPin = 9;
// Small servo pin
int smallPin = 8;

// Define servos
Servo bigServo;
Servo smallServo;

void setup_servos() {
  // Attach pins
  bigServo.attach(9);
  smallServo.attach(8);

  // Set for init position
  bigServo.write(100);
}

void grab() {
    bigServo.write(20);
    delay(20);             
    bigServo.write(0);
    delay(1500);
    smallServo.write(150);
    delay(1500);
    bigServo.write(150);
    delay(1500);
    smallServo.write(125);
    delay(1500);               
}

// 9 er stor motor
// 8 er lille motor
//servo 9 OPPE=160
//servo 9 NEDE=0
//servo 8 lukket=130
//servo 8 åben=70
