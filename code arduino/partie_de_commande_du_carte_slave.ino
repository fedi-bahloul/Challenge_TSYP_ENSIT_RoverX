#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Send forward command with speed 150
  sendCommand('F', 150);
  delay(2000);  // Wait for 2 seconds

  // Send backward command with speed 100
  sendCommand('B', 100);
  delay(2000);  // Wait for 2 seconds

  // Send turn left command with speed 120
  sendCommand('L', 120);
  delay(2000);  // Wait for 2 seconds

  // Send turn right command with speed 120
  sendCommand('R', 120);
  delay(2000);  // Wait for 2 seconds
}

void sendCommand(char command, int speed) {
  Wire.beginTransmission(8);  // Replace 8 with the slave address you set
  Wire.write(command);
  Wire.write(speed);
  Wire.endTransmission();
}
