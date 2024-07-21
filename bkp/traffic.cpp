#include <Arduino.h>
// Проет світлофора
int redled = 10;   // initialize digital pin 10.
int yellowled = 6; // initialize digital pin 7.
int blueled = 3;   // initialize digital pin 4.
void setup()
{
    Serial.begin(9600);         // set up Serial library at 9600 bps
    pinMode(redled, OUTPUT);    // set the pin with red LED as “output”
    pinMode(yellowled, OUTPUT); // set the pin with yellow LED as “output”
    pinMode(blueled, OUTPUT);   // set the pin with blue LED as “output”
    Serial.println("Світлофор запускається");
    for (int x = 0; x < 5; x++) // blink for 5 times
    {
        digitalWrite(yellowled, HIGH); // turn on red LED
        delay(1000);                   // wait 1 second
        digitalWrite(yellowled, LOW);  // turn off red LED
        delay(1000);                   // wait 0.5 second
    }
    Serial.println("Перевірка завершена, світлофор працює");
}

void loop()
{
    digitalWrite(redled, HIGH);    // turn on red LED
    delay(10000);                  // wait 10 second
    digitalWrite(yellowled, HIGH); // turn on yellow LED
    delay(2000);                   // wait 2 seconds
    digitalWrite(redled, LOW);     // turn off red LED
    digitalWrite(yellowled, LOW);  // turn off yellow LED
    digitalWrite(blueled, HIGH);   //// turn on blue LED
    delay(10000);                  // wait 10 seconds
    digitalWrite(blueled, LOW);    // turn off blue LED
    for (int i = 0; i < 3; i++)    // blinks for 3 times
    {
        delay(500);                  // wait 0.5 second
        digitalWrite(blueled, HIGH); // turn on blue LED
        delay(500);                  // wait 0.5 second
        digitalWrite(blueled, LOW);  // turn off blue LED
    }
    delay(500);                    // wait 0.5 second
    digitalWrite(yellowled, HIGH); // turn on yellow LED
    delay(2000);                   // wait 2 seconds
    digitalWrite(yellowled, LOW);  // turn off yellow LED
}
