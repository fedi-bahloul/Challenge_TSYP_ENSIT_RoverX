#include <Wire.h>

const int motor1Pin1 = 2;                             // Motor 1 control pin 1
const int motor1Pin2 = 3;                             // Motor 1 control pin 2
const int motor2Pin1 = 4;                             // Motor 2 control pin 1
const int motor2Pin2 = 5;                             // Motor 2 control pin 2

const int speedPin1 = 6;                              // Motor 1 speed control pin
const int speedPin2 = 9;                              // Motor 2 speed control pin
const int servoPin = 10;                              // Servo control pin

Servo steeringServo;                                  // Create a servo object


void setup() {
  Wire.begin(8);                                      // Set Arduino address as 8
  Wire.onReceive(receiveEvent);                       // Set function to handle received data
  Serial.begin(9600);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);

   steeringServo.attach(servoPin);                    // Attach the servo to its pin
}

void loop() {
  // Your main loop code, if needed
}

void receiveEvent() {
  if (Wire.available() >= 2) {
    char command = Wire.read();
    int speed = Wire.read();

    switch (command) {
      case 'F':
        driveForward(speed);
        break;
      case 'L':
        turnLeft(speed);
        break;
      case 'R':
        turnRight(speed);
        break;
      case 'B':
        driveBackward(speed);
        break;
      default:
        // Handle invalid command
        break;
    }
  }
}

void driveForward(int speed) {
  steeringServo.write(90);
  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
}

void driveBackward(int speed) {
  steeringServo.write(90);
  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft(int speed) {
  steeringServo.write(0);
  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
}

void turnRight(int speed) {
  steeringServo.write(180);
  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
}
