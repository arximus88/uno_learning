#include <Arduino.h>
#include <Servo.h>

int trigPin = 12;  // Pin Trig attach to 12
int echoPin = 13;  // Pin Echo attach to 13
long duration, cm; // Define the variables of duration, cm, and inches
int pos = 90;      // Save the variables of angle
int led = 9;       // Define the LED pin
int ledpwm = 0;    // Define the LED brightness

Servo myservo; // set the servo

void setup()
{
    // Serial Port begin
    Serial.begin(9600); // Set the baud rate to 9600
    myservo.attach(10); // Connect the servo with digital port 10
    // Define input and output
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT); // Initialize the LED pin to output mode
}

void loop()
{
    // The trigger pin is set to low level for 2us
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // At least give 10us high level trigger
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // The time in high level equals the time gap between the transmission and the return of the ultrasonic sound
    duration = pulseIn(echoPin, HIGH);

    // Translate into distance
    cm = (duration / 2) / 29.1; // Convert to cm

    if (cm >= 0 && cm <= 100)
    {
        ledpwm = map(cm, 0, 100, 255, 0); // Convert the distance to the brightness of the LED
        analogWrite(led, ledpwm);         // Set the brightness of the LED
    }
    else
    {
        analogWrite(led, 0); // Turn off the LED if the distance is out of range
    }

    // Serial port print it
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.print(" cm, LED brightness: ");
    Serial.print(ledpwm);
    Serial.println();

    switch (Serial.read()) // Read the serial port
    {
    case 'a': // Turn the servo motor to the left
        pos = pos + 5;
        if (pos > 180)
        {
            pos = 180;
        }
        myservo.write(pos);
        Serial.println(pos);
        break;
    case 'd': // Turn the servo motor to the right
        pos = pos - 5;
        if (pos < 0)
        {
            pos = 0;
        }
        myservo.write(pos);
        Serial.println(pos);
        break;
    case 's': // Turn the servo motor to the middle
        pos = 90;
        myservo.write(pos);
        Serial.println(pos);
        break;
    default:
        break;
    }

    delay(50);
}