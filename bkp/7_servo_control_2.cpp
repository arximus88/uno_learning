/* 
 * Control the servo motor with the keyboard
 * 'a' : Turn the servo motor to the left
 * 'd' : Turn the servo motor to the right
 * 's' : Turn the servo motor to the middle
*/

#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // set the servo
int pos = 90;    // Save the variables of angle
void setup() {
  Serial.begin(9600);  // Initialize the serial port
  myservo.attach(10);  //Connect the servo with digital port 10
}
void loop() {
switch (Serial.read()) {
    case 'a':
      pos = pos + 5;
      if (pos > 180) {
        pos = 180;
      }
      myservo.write(pos);
      Serial.println(pos);
      break;
    case 'd':
      pos = pos - 5;
      if (pos < 0) {
        pos = 0;
      }
      myservo.write(pos);
      Serial.println(pos);
      break;
    case 's':
      pos = 90;
      myservo.write(pos);
      Serial.println(pos);
      break;
    default:
      break;
  }
  delay(15);
}